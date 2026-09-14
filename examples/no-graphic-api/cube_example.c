// cube_example.c - Interactive 3D Cubes in Native Window (Cross-Platform: Win32 & Linux/XCB)
//
// Implements Sebastian Aaltonen's "No Graphics API" architecture:
//   - Manual vertex pulling via 64-bit GPU virtual addresses (GL_EXT_buffer_reference)
//   - Single 64-bit root pointer per draw call passed through push constants
//   - Zero vertex buffers / descriptor sets / root signatures / fixed-function IA
//   - Direct CPU-GPU memory mapping (gpu_malloc with GPU_MemoryKind_Default)
//   - Dynamic rendering (Vulkan 1.3 - no VkRenderPass or VkFramebuffer)
//   - Native window presentation:
//       Windows: Win32 API (CreateWindowExA, PeekMessageA, VK_KHR_win32_surface)
//       Linux:   XCB API (xcb_create_window, xcb_poll_for_event, VK_KHR_xcb_surface)
//
// Codebase style: Ryan Fleury & Sean Barrett (raddebugger)
// Build (Linux):   ./build_cubes.sh
// Build (Windows): build_cubes.bat (or x86_64-w64-mingw32-gcc via build_cubes_win32.sh)

#if defined(_WIN32)
# ifndef WIN32_LEAN_AND_MEAN
#  define WIN32_LEAN_AND_MEAN
# endif
# ifndef NOMINMAX
#  define NOMINMAX
# endif
# include <windows.h>
#else
# define _POSIX_C_SOURCE 199309L
# include <xcb/xcb.h>
# include <time.h>
#endif

#define GPU_IMPLEMENTATION
#include "gpu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

////////////////////////////////
//~ rjf: Embedded SPIR-V Shader Bytecode

static const uint32_t g_cube_vert_spv[] =
#include "cube_vert_spv.h"
;

static const uint32_t g_cube_frag_spv[] =
#include "cube_frag_spv.h"
;

////////////////////////////////
//~ rjf: Linear Math (Vectors & Matrices)

#define PI32 3.14159265358979323846f
#define RadiansFromDegrees(deg) ((deg) * (PI32 / 180.0f))

typedef struct Vec3 Vec3;
struct Vec3 {
    F32 x, y, z;
};

typedef struct Vec4 Vec4;
struct Vec4 {
    F32 x, y, z, w;
};

typedef struct Mat4 Mat4;
struct Mat4 {
    F32 m[4][4]; // [col][row] column-major for Vulkan/GLSL
};

internal Mat4
mat4_identity(void)
{
    Mat4 r;
    GPU_MemoryZeroStruct(&r);
    r.m[0][0] = 1.0f;
    r.m[1][1] = 1.0f;
    r.m[2][2] = 1.0f;
    r.m[3][3] = 1.0f;
    return r;
}

internal Mat4
mat4_mul(Mat4 a, Mat4 b)
{
    Mat4 r;
    for (int col = 0; col < 4; col += 1) {
        for (int row = 0; row < 4; row += 1) {
            r.m[col][row] = a.m[0][row] * b.m[col][0] +
                            a.m[1][row] * b.m[col][1] +
                            a.m[2][row] * b.m[col][2] +
                            a.m[3][row] * b.m[col][3];
        }
    }
    return r;
}

internal Mat4
mat4_translate(F32 tx, F32 ty, F32 tz)
{
    Mat4 r = mat4_identity();
    r.m[3][0] = tx;
    r.m[3][1] = ty;
    r.m[3][2] = tz;
    return r;
}

internal Mat4
mat4_scale(F32 sx, F32 sy, F32 sz)
{
    Mat4 r = mat4_identity();
    r.m[0][0] = sx;
    r.m[1][1] = sy;
    r.m[2][2] = sz;
    return r;
}

internal Mat4
mat4_rotate_x(F32 angle_rad)
{
    Mat4 r = mat4_identity();
    F32 c = cosf(angle_rad);
    F32 s = sinf(angle_rad);
    r.m[1][1] =  c;
    r.m[2][1] = -s;
    r.m[1][2] =  s;
    r.m[2][2] =  c;
    return r;
}

internal Mat4
mat4_rotate_y(F32 angle_rad)
{
    Mat4 r = mat4_identity();
    F32 c = cosf(angle_rad);
    F32 s = sinf(angle_rad);
    r.m[0][0] =  c;
    r.m[2][0] =  s;
    r.m[0][2] = -s;
    r.m[2][2] =  c;
    return r;
}

internal Mat4
mat4_rotate_z(F32 angle_rad)
{
    Mat4 r = mat4_identity();
    F32 c = cosf(angle_rad);
    F32 s = sinf(angle_rad);
    r.m[0][0] =  c;
    r.m[1][0] = -s;
    r.m[0][1] =  s;
    r.m[1][1] =  c;
    return r;
}

// Vulkan perspective projection: [0, 1] depth range, Y flipped
internal Mat4
mat4_perspective(F32 fov_rad, F32 aspect, F32 z_near, F32 z_far)
{
    Mat4 r;
    GPU_MemoryZeroStruct(&r);
    F32 tan_half_fov = tanf(fov_rad / 2.0f);
    r.m[0][0] = 1.0f / (aspect * tan_half_fov);
    r.m[1][1] = -1.0f / tan_half_fov; // flip Y for Vulkan
    r.m[2][2] = z_far / (z_near - z_far);
    r.m[2][3] = -1.0f;
    r.m[3][2] = -(z_far * z_near) / (z_far - z_near);
    return r;
}

////////////////////////////////
//~ rjf: Scene Geometry & Root Data Structs

typedef struct Vertex Vertex;
struct Vertex {
    Vec3 pos;
    Vec3 normal;
    Vec4 color;
};

typedef struct CubeRootData CubeRootData;
struct CubeRootData {
    U64  vertices_ptr; // 64-bit GPU pointer to Vertex array (GL_EXT_buffer_reference)
    Mat4 mvp;          // Model-View-Projection matrix
    Mat4 model;        // Model matrix for lighting normals
};

typedef struct CubeInstance CubeInstance;
struct CubeInstance {
    Vec3 pos;
    Vec3 rot_deg;
    Vec3 rot_speed;
    F32  scale;
};

////////////////////////////////
//~ rjf: Cube Geometry Generator (36 vertices with distinct face normals & colors)

internal U32
generate_cube_vertices(Vertex *out_vertices)
{
    // 6 faces * 2 triangles * 3 vertices = 36 vertices
    // Cube centered at origin with size [-0.5, +0.5]
    static const Vec3 face_normals[6] = {
        {  0.0f,  0.0f,  1.0f }, // 0: Front  (+Z)
        {  0.0f,  0.0f, -1.0f }, // 1: Back   (-Z)
        {  1.0f,  0.0f,  0.0f }, // 2: Right  (+X)
        { -1.0f,  0.0f,  0.0f }, // 3: Left   (-X)
        {  0.0f,  1.0f,  0.0f }, // 4: Top    (+Y)
        {  0.0f, -1.0f,  0.0f }, // 5: Bottom (-Y)
    };

    static const Vec4 face_colors[6] = {
        { 0.95f, 0.26f, 0.21f, 1.0f }, // Red / Coral (Front)
        { 0.00f, 0.74f, 0.83f, 1.0f }, // Cyan / Teal (Back)
        { 0.30f, 0.69f, 0.31f, 1.0f }, // Emerald Green (Right)
        { 0.61f, 0.15f, 0.69f, 1.0f }, // Purple (Left)
        { 1.00f, 0.76f, 0.03f, 1.0f }, // Amber / Gold (Top)
        { 0.25f, 0.32f, 0.71f, 1.0f }, // Indigo (Bottom)
    };

    static const Vec3 face_quads[6][4] = {
        // Front (+Z)
        { { -0.5f, -0.5f,  0.5f }, {  0.5f, -0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }, { -0.5f,  0.5f,  0.5f } },
        // Back (-Z)
        { {  0.5f, -0.5f, -0.5f }, { -0.5f, -0.5f, -0.5f }, { -0.5f,  0.5f, -0.5f }, {  0.5f,  0.5f, -0.5f } },
        // Right (+X)
        { {  0.5f, -0.5f,  0.5f }, {  0.5f, -0.5f, -0.5f }, {  0.5f,  0.5f, -0.5f }, {  0.5f,  0.5f,  0.5f } },
        // Left (-X)
        { { -0.5f, -0.5f, -0.5f }, { -0.5f, -0.5f,  0.5f }, { -0.5f,  0.5f,  0.5f }, { -0.5f, -0.5f, -0.5f } },
        // Top (+Y)
        { { -0.5f,  0.5f,  0.5f }, {  0.5f,  0.5f,  0.5f }, {  0.5f,  0.5f, -0.5f }, { -0.5f,  0.5f, -0.5f } },
        // Bottom (-Y)
        { { -0.5f, -0.5f, -0.5f }, {  0.5f, -0.5f, -0.5f }, {  0.5f, -0.5f,  0.5f }, { -0.5f, -0.5f,  0.5f } },
    };

    static const U32 quad_indices[6] = { 0, 1, 2, 0, 2, 3 };

    U32 v_idx = 0;
    for (U32 face = 0; face < 6; face += 1) {
        for (U32 i = 0; i < 6; i += 1) {
            U32 corner = quad_indices[i];
            out_vertices[v_idx].pos    = face_quads[face][corner];
            out_vertices[v_idx].normal = face_normals[face];
            out_vertices[v_idx].color  = face_colors[face];
            v_idx += 1;
        }
    }

    return v_idx; // 36
}

////////////////////////////////
//~ rjf: Win32 Window Procedure

#if defined(_WIN32)
internal LRESULT CALLBACK
win32_window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg) {
        case WM_CLOSE:
        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        } break;
        case WM_KEYDOWN: {
            if (wparam == VK_ESCAPE || wparam == 'Q') {
                PostQuitMessage(0);
                return 0;
            }
        } break;
    }
    return DefWindowProcA(hwnd, msg, wparam, lparam);
}
#endif

////////////////////////////////
//~ rjf: Main Program

int
main(void)
{
    printf("============================================================\n");
    printf("   \"No Graphics API\" Interactive 3D Cubes                   \n");
    printf("   Pure C / Zero External Libs / Cross-Platform (Win32/X11) \n");
    printf("============================================================\n\n");

    const U32 k_width  = 800;
    const U32 k_height = 600;

    //- 1. Create Native Window
    GPU_WindowHandle win_handle;
    GPU_MemoryZeroStruct(&win_handle);

#if defined(_WIN32)
    HINSTANCE hinstance = GetModuleHandleA(NULL);
    WNDCLASSEXA wc = {
        .cbSize = sizeof(WNDCLASSEXA),
        .style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
        .lpfnWndProc = win32_window_proc,
        .hInstance = hinstance,
        .hCursor = LoadCursorA(NULL, IDC_ARROW),
        .lpszClassName = "NoGfxApiCubeClass",
    };
    RegisterClassExA(&wc);

    RECT rect = { 0, 0, (LONG)k_width, (LONG)k_height };
    AdjustWindowRect(&rect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);
    HWND hwnd = CreateWindowExA(
        0,
        wc.lpszClassName,
        "No Graphics API - 3D Cubes (Win32 Window)",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        rect.right - rect.left,
        rect.bottom - rect.top,
        NULL, NULL, hinstance, NULL
    );
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    win_handle.hinstance = (void *)hinstance;
    win_handle.hwnd      = (void *)hwnd;
    printf("[1/6] Created Win32 Window (%ux%u)\n", k_width, k_height);

#elif defined(__linux__)
    xcb_connection_t *connection = xcb_connect(NULL, NULL);
    if (xcb_connection_has_error(connection)) {
        fprintf(stderr, "[ERROR] Failed to connect to X server via XCB\n");
        return 1;
    }

    const xcb_setup_t *setup = xcb_get_setup(connection);
    xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
    xcb_screen_t *screen = iter.data;
    if (!screen) {
        fprintf(stderr, "[ERROR] Failed to obtain XCB default screen\n");
        xcb_disconnect(connection);
        return 1;
    }

    xcb_window_t window = xcb_generate_id(connection);
    U32 event_mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    U32 event_values[2] = {
        screen->black_pixel,
        XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_STRUCTURE_NOTIFY
    };

    xcb_create_window(
        connection,
        XCB_COPY_FROM_PARENT,
        window,
        screen->root,
        0, 0,
        k_width, k_height,
        0,
        XCB_WINDOW_CLASS_INPUT_OUTPUT,
        screen->root_visual,
        event_mask,
        event_values
    );

    const char *title = "No Graphics API - 3D Cubes (XCB Window)";
    xcb_change_property(
        connection,
        XCB_PROP_MODE_REPLACE,
        window,
        XCB_ATOM_WM_NAME,
        XCB_ATOM_STRING,
        8,
        (U32)strlen(title),
        title
    );

    xcb_intern_atom_cookie_t wm_protocols_cookie = xcb_intern_atom(connection, 1, 12, "WM_PROTOCOLS");
    xcb_intern_atom_reply_t *wm_protocols_reply = xcb_intern_atom_reply(connection, wm_protocols_cookie, 0);

    xcb_intern_atom_cookie_t wm_delete_window_cookie = xcb_intern_atom(connection, 0, 16, "WM_DELETE_WINDOW");
    xcb_intern_atom_reply_t *wm_delete_window_reply = xcb_intern_atom_reply(connection, wm_delete_window_cookie, 0);

    xcb_atom_t wm_delete_window_atom = wm_delete_window_reply ? wm_delete_window_reply->atom : 0;
    if (wm_protocols_reply && wm_delete_window_reply) {
        xcb_change_property(
            connection,
            XCB_PROP_MODE_REPLACE,
            window,
            wm_protocols_reply->atom,
            XCB_ATOM_ATOM,
            32,
            1,
            &wm_delete_window_reply->atom
        );
    }
    free(wm_protocols_reply);
    free(wm_delete_window_reply);

    xcb_map_window(connection, window);
    xcb_flush(connection);

    win_handle.connection = (void *)connection;
    win_handle.window     = (U32)window;
    printf("[1/6] Created XCB Window (%ux%u)\n", k_width, k_height);
#endif

    //- 2. Create GPU Device with WSI surface support
    GPU_DeviceDesc dev_desc = {
        .enable_validation = 0,
        .enable_surface = 1,
        .app_name = "no-gfx-api-3-cubes",
    };
    GPU_Device *device = gpu_device_create(&dev_desc);
    GPU_ASSERT(device && "Failed to create GPU device");
    GPU_Queue *queue = gpu_queue_create(device);
    printf("[2/6] GPU Device initialized with WSI swapchain support\n");

    //- 3. Create Swapchain (cross-platform)
    GPU_Swapchain *swapchain = gpu_swapchain_create(device, &win_handle, k_width, k_height);
    GPU_ASSERT(swapchain && "Failed to create swapchain");
    printf("[3/6] Swapchain created (Format: %u, Images: %u)\n",
           gpu_swapchain_format(swapchain), swapchain->image_count);

    //- 4. Allocate Geometry in DEFAULT memory (CUDA-style gpu_malloc)
    // Manual vertex pulling: shader reads vertex buffer via direct 64-bit device address
    Vertex cube_vertices[36];
    generate_cube_vertices(cube_vertices);

    GPU_Alloc *vertex_alloc = gpu_malloc(device, sizeof(cube_vertices), GPU_MemoryKind_Default);
    GPU_MemoryCopy(gpu_alloc_cpu_ptr(vertex_alloc), cube_vertices, sizeof(cube_vertices));
    U64 vertex_gpu_addr = gpu_alloc_device_addr(vertex_alloc);
    printf("[4/6] Uploaded 36 vertices (1.4 KB) to GPU memory (Address: 0x%llx)\n",
           (unsigned long long)vertex_gpu_addr);

    //- 5. Create Depth Target & Graphics Pipeline matching swapchain
    GPU_TextureDesc depth_desc = {
        .width  = k_width,
        .height = k_height,
        .depth  = 1,
        .mip_levels = 1,
        .format = GPU_Format_D32_Float,
        .is_depth_stencil = 1,
    };
    GPU_Texture *depth_target = gpu_texture_create(device, &depth_desc, 0);

    GPU_RasterDesc raster_desc = {
        .cull_mode = GPU_CullMode_None,
        .wireframe = 0,
        .color_format = gpu_swapchain_format(swapchain),
        .depth_format = GPU_Format_D32_Float,
    };
    GPU_Pipeline *pipeline = gpu_pipeline_graphics_create(
        device,
        (const U8 *)g_cube_vert_spv, sizeof(g_cube_vert_spv),
        (const U8 *)g_cube_frag_spv, sizeof(g_cube_frag_spv),
        &raster_desc
    );
    GPU_ASSERT(pipeline && "Failed to create graphics pipeline");
    printf("[5/6] Graphics Pipeline & D32_Float Depth Target created\n");

    //- 6. Set Up Transformation Matrices & Root Data for 3 Cubes
    // Sebastian Aaltonen's model: Single 64-bit root pointer per draw call!
    GPU_Alloc *roots_alloc = gpu_malloc(device, sizeof(CubeRootData) * 3, GPU_MemoryKind_Default);
    CubeRootData *roots_cpu = (CubeRootData *)gpu_alloc_cpu_ptr(roots_alloc);

    Mat4 proj = mat4_perspective(RadiansFromDegrees(50.0f), (F32)k_width / (F32)k_height, 0.1f, 100.0f);
    Mat4 view = mat4_translate(0.0f, 0.0f, 0.0f); // Camera at origin looking down -Z
    Mat4 proj_view = mat4_mul(proj, view);

    CubeInstance cubes[3] = {
        // Left Cube
        { { -2.1f, 0.0f, -5.2f }, {  28.0f,  40.0f,   0.0f }, { 35.0f,  50.0f,  20.0f }, 1.15f },
        // Center Cube
        { {  0.0f, 0.0f, -4.3f }, { -32.0f,  45.0f,  20.0f }, { 45.0f,  70.0f,  30.0f }, 1.30f },
        // Right Cube
        { {  2.1f, 0.0f, -5.2f }, {  45.0f, -30.0f, -15.0f }, { 30.0f, -45.0f,  40.0f }, 1.15f },
    };

    printf("[6/6] Starting interactive real-time render loop...\n");
    printf("      [Press ESC or close window to exit]\n\n");

#if defined(_WIN32)
    LARGE_INTEGER perf_freq, last_counter;
    QueryPerformanceFrequency(&perf_freq);
    QueryPerformanceCounter(&last_counter);
#else
    struct timespec last_time;
    clock_gettime(CLOCK_MONOTONIC, &last_time);
#endif

    B32 running = 1;
    U64 frame_counter = 0;

    while (running) {
        //- Poll Window Events
#if defined(_WIN32)
        MSG msg;
        while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                running = 0;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }
#elif defined(__linux__)
        xcb_generic_event_t *event;
        while ((event = xcb_poll_for_event(connection)) != 0) {
            U8 event_code = event->response_type & ~0x80;
            switch (event_code) {
                case XCB_CLIENT_MESSAGE: {
                    xcb_client_message_event_t *cm = (xcb_client_message_event_t *)event;
                    if (cm->data.data32[0] == wm_delete_window_atom) {
                        running = 0;
                    }
                } break;

                case XCB_KEY_PRESS: {
                    xcb_key_press_event_t *kp = (xcb_key_press_event_t *)event;
                    // Keycode 9 is Escape on Linux X11 keyboards, 24 is 'q'
                    if (kp->detail == 9 || kp->detail == 24) {
                        running = 0;
                    }
                } break;

                case XCB_DESTROY_NOTIFY: {
                    running = 0;
                } break;
            }
            free(event);
        }
#endif

        if (!running) break;

        //- Compute Delta Time
#if defined(_WIN32)
        LARGE_INTEGER now_counter;
        QueryPerformanceCounter(&now_counter);
        F32 dt = (F32)(now_counter.QuadPart - last_counter.QuadPart) / (F32)perf_freq.QuadPart;
        last_counter = now_counter;
#else
        struct timespec now_time;
        clock_gettime(CLOCK_MONOTONIC, &now_time);
        F32 dt = (F32)(now_time.tv_sec - last_time.tv_sec) +
                 (F32)(now_time.tv_nsec - last_time.tv_nsec) * 1e-9f;
        last_time = now_time;
#endif

        if (dt > 0.1f) dt = 0.1f; // clamp delta time if stalled

        //- Update Cube Rotations & MVP Matrices
        for (U32 i = 0; i < 3; i += 1) {
            cubes[i].rot_deg.x += cubes[i].rot_speed.x * dt;
            cubes[i].rot_deg.y += cubes[i].rot_speed.y * dt;
            cubes[i].rot_deg.z += cubes[i].rot_speed.z * dt;

            Mat4 T = mat4_translate(cubes[i].pos.x, cubes[i].pos.y, cubes[i].pos.z);
            Mat4 Rx = mat4_rotate_x(RadiansFromDegrees(cubes[i].rot_deg.x));
            Mat4 Ry = mat4_rotate_y(RadiansFromDegrees(cubes[i].rot_deg.y));
            Mat4 Rz = mat4_rotate_z(RadiansFromDegrees(cubes[i].rot_deg.z));
            Mat4 S = mat4_scale(cubes[i].scale, cubes[i].scale, cubes[i].scale);

            Mat4 rot = mat4_mul(Rz, mat4_mul(Ry, Rx));
            Mat4 model = mat4_mul(T, mat4_mul(rot, S));
            Mat4 mvp = mat4_mul(proj_view, model);

            roots_cpu[i].vertices_ptr = vertex_gpu_addr;
            roots_cpu[i].mvp = mvp;
            roots_cpu[i].model = model;
        }

        //- Acquire Next Swapchain Backbuffer
        GPU_Texture *backbuffer = gpu_swapchain_acquire(device, swapchain);
        if (!backbuffer) continue;

        //- Record Commands
        GPU_CmdBuf *cb = gpu_cmd_begin(device, queue);

        gpu_cmd_set_viewport(cb, 0.0f, 0.0f, (F32)k_width, (F32)k_height, 0.0f, 1.0f);
        gpu_cmd_set_scissor(cb, 0, 0, k_width, k_height);
        gpu_cmd_set_pipeline(cb, pipeline);

        // Dynamic Rendering (Vulkan 1.3)
        gpu_cmd_begin_rendering(cb, backbuffer, depth_target, k_width, k_height);

        // Draw the 3 cubes using direct 64-bit root pointers!
        for (U32 i = 0; i < 3; i += 1) {
            U64 root_gpu_ptr = gpu_host_to_device_ptr(device, roots_alloc, &roots_cpu[i]);
            // 36 vertices, manual vertex pulling in shader
            gpu_cmd_draw(cb, root_gpu_ptr, 0, 36, 1);
        }

        gpu_cmd_end_rendering(cb);

        //- Submit & Present to Window
        gpu_swapchain_submit_and_present(device, queue, swapchain, cb);
        frame_counter += 1;
    }

    printf("\nRendered %llu frames. Releasing resources...\n", (unsigned long long)frame_counter);

    //- Cleanup Resources
    gpu_device_wait_idle(device);
    gpu_free(device, roots_alloc);
    gpu_free(device, vertex_alloc);
    gpu_pipeline_destroy(device, pipeline);
    gpu_texture_destroy(device, depth_target);
    gpu_swapchain_destroy(device, swapchain);
    gpu_queue_destroy(device, queue);
    gpu_device_destroy(device);

#if defined(_WIN32)
    DestroyWindow(hwnd);
#elif defined(__linux__)
    xcb_destroy_window(connection, window);
    xcb_disconnect(connection);
#endif

    printf("[SUCCESS] All resources released cleanly. Exiting.\n");
    return 0;
}
