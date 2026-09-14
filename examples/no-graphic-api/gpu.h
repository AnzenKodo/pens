// gpu.h - No Graphics API: A Minimal GPU Abstraction over Vulkan
//
// Based on Sebastian Aaltonen's "No Graphics API" (2025)
// Implementation style: Ryan Fleury / Sean Barrett (raddebugger)
//
// USAGE:
//   #include "gpu.h"          // declarations only
//   #define GPU_IMPLEMENTATION
//   #include "gpu.h"          // pulls in the implementation
//
// CONFIGURATION:
//   #define GPU_ASSERT(x)      - custom assert (default: libc assert)
//   #define GPU_MALLOC(sz)     - custom CPU allocator (default: malloc)
//   #define GPU_FREE(p)        - custom CPU deallocator (default: free)
//   #define GPU_STATIC          - make all functions static
//
// LICENSE: Public Domain / MIT (your choice)

#ifndef GPU_H
#define GPU_H

////////////////////////////////
//~ sa: Operating System Detection

#if defined(_WIN32) || defined(_WIN64)
# define GPU_OS_WINDOWS 1
#elif defined(__linux__) || defined(__gnu_linux__)
# define GPU_OS_LINUX 1
#elif defined(__APPLE__) && defined(__MACH__)
# define GPU_OS_MAC 1
#else
# define GPU_OS_UNKNOWN 1
#endif

#if defined(GPU_OS_WINDOWS)
# define GPU_VK_CALL __stdcall
#else
# define GPU_VK_CALL
#endif

////////////////////////////////
//~ sa: Foreign Includes

#include <stdint.h>
#include <stddef.h>

////////////////////////////////
//~ sa: Codebase Keywords

#ifndef internal
# define internal      static
#endif
#ifndef global
# define global        static
#endif
#ifndef local_persist
# define local_persist static
#endif

////////////////////////////////
//~ sa: Configuration Defaults

#ifndef GPU_ASSERT
# include <assert.h>
# define GPU_ASSERT(x) assert(x)
#endif

#ifndef GPU_MALLOC
# include <stdlib.h>
# define GPU_MALLOC(sz) malloc(sz)
# define GPU_FREE(p)    free(p)
#endif

#ifdef GPU_STATIC
# define GPU_API static
#else
# define GPU_API extern
#endif

////////////////////////////////
//~ sa: Base Types

typedef uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;
typedef int8_t   S8;
typedef int16_t  S16;
typedef int32_t  S32;
typedef int64_t  S64;
typedef S32      B32;
typedef float    F32;
typedef double   F64;

////////////////////////////////
//~ sa: Base Macros

#define GPU_ArrayCount(a)       (sizeof(a) / sizeof((a)[0]))
#define GPU_Min(a, b)           (((a) < (b)) ? (a) : (b))
#define GPU_Max(a, b)           (((a) > (b)) ? (a) : (b))
#define GPU_Clamp(lo, x, hi)    (((x) < (lo)) ? (lo) : ((x) > (hi)) ? (hi) : (x))
#define GPU_AlignUp(x, a)       (((x) + ((a) - 1)) & ~((a) - 1))
#define GPU_KB(n)               (((U64)(n)) << 10)
#define GPU_MB(n)               (((U64)(n)) << 20)
#define GPU_GB(n)               (((U64)(n)) << 30)

#define GPU_MemoryZero(p, sz)       memset((p), 0, (sz))
#define GPU_MemoryZeroStruct(p)     GPU_MemoryZero((p), sizeof(*(p)))
#define GPU_MemoryCopy(d, s, sz)    memmove((d), (s), (sz))

////////////////////////////////
//~ sa: Memory Kind Enum
//
// Three memory types matching modern GPU hardware:
//   DEFAULT  - CPU-mapped, write-combined (UMA / ReBAR). CPU writes, GPU reads.
//   GPU_ONLY - Private high-bandwidth VRAM. Supports DCC/lossless compression.
//   READBACK - GPU writes, CPU reads (cached for fast readback).

typedef enum GPU_MemoryKind {
    GPU_MemoryKind_Default,
    GPU_MemoryKind_GpuOnly,
    GPU_MemoryKind_Readback,
    GPU_MemoryKind_COUNT,
} GPU_MemoryKind;

////////////////////////////////
//~ sa: Cull Mode

typedef enum GPU_CullMode {
    GPU_CullMode_None,
    GPU_CullMode_FrontCCW,
    GPU_CullMode_FrontCW,
    GPU_CullMode_All,
    GPU_CullMode_COUNT,
} GPU_CullMode;

////////////////////////////////
//~ sa: Depth Flags

typedef enum GPU_DepthFlags {
    GPU_DepthFlags_None  = 0x0,
    GPU_DepthFlags_Read  = 0x1,
    GPU_DepthFlags_Write = 0x2,
} GPU_DepthFlags;

////////////////////////////////
//~ sa: Pipeline Stage Flags (bitmask)
//
// Used for coarse-grained barrier stage masks.
// Maps directly to VkPipelineStageFlagBits2.

typedef enum GPU_StageFlags {
    GPU_StageFlags_None            = 0x0,
    GPU_StageFlags_Transfer        = 0x1,
    GPU_StageFlags_Compute         = 0x2,
    GPU_StageFlags_VertexShader    = 0x4,
    GPU_StageFlags_PixelShader     = 0x8,
    GPU_StageFlags_RasterColorOut  = 0x10,
    GPU_StageFlags_RasterDepthOut  = 0x20,
    GPU_StageFlags_All             = 0xFFFFFFFF,
} GPU_StageFlags;

////////////////////////////////
//~ sa: Hazard Flags (bitmask)
//
// Non-coherent cache invalidation hints. Only needed for:
//   DESCRIPTORS    - sampler internal descriptor cache (after heap writes)
//   DRAW_ARGUMENTS - command processor argument prefetch (before indirect)

typedef enum GPU_HazardFlags {
    GPU_HazardFlags_None          = 0x0,
    GPU_HazardFlags_Descriptors   = 0x1,
    GPU_HazardFlags_DrawArguments = 0x2,
} GPU_HazardFlags;

////////////////////////////////
//~ sa: Texture Format

typedef enum GPU_Format {
    GPU_Format_Undefined,
    GPU_Format_R8_UNorm,
    GPU_Format_R8G8_UNorm,
    GPU_Format_R8G8B8A8_UNorm,
    GPU_Format_R8G8B8A8_SRGB,
    GPU_Format_B8G8R8A8_UNorm,
    GPU_Format_B8G8R8A8_SRGB,
    GPU_Format_R16_Float,
    GPU_Format_R16G16_Float,
    GPU_Format_R16G16B16A16_Float,
    GPU_Format_R32_Float,
    GPU_Format_R32G32_Float,
    GPU_Format_R32G32B32A32_Float,
    GPU_Format_R32_UInt,
    GPU_Format_R16_UInt,
    GPU_Format_D16_UNorm,
    GPU_Format_D24_UNorm_S8_UInt,
    GPU_Format_D32_Float,
    GPU_Format_D32_Float_S8_UInt,
    GPU_Format_COUNT,
} GPU_Format;

////////////////////////////////
//~ sa: Forward Declarations (Opaque Handles)

typedef struct GPU_Device         GPU_Device;
typedef struct GPU_Alloc          GPU_Alloc;
typedef struct GPU_Texture        GPU_Texture;
typedef struct GPU_Pipeline       GPU_Pipeline;
typedef struct GPU_DepthStencilState GPU_DepthStencilState;
typedef struct GPU_BlendState     GPU_BlendState;
typedef struct GPU_Queue          GPU_Queue;
typedef struct GPU_CmdBuf         GPU_CmdBuf;
typedef struct GPU_Semaphore      GPU_Semaphore;
typedef struct GPU_Swapchain      GPU_Swapchain;

////////////////////////////////
//~ sa: Descriptor Structs

typedef struct GPU_DeviceDesc GPU_DeviceDesc;
struct GPU_DeviceDesc {
    B32 enable_validation;
    B32 enable_surface; // Set to 1 to enable VK_KHR_surface + VK_KHR_xcb_surface + VK_KHR_swapchain
    B32 enable_gpu_printf;
    const char *app_name;
};

typedef struct GPU_TextureDesc GPU_TextureDesc;
struct GPU_TextureDesc {
    U32 width;
    U32 height;
    U32 depth;         // 1 for 2D textures
    U32 mip_levels;    // 0 = auto full mip chain
    GPU_Format format;
    B32 is_render_target;
    B32 is_depth_stencil;
    B32 is_storage;
};

typedef struct GPU_TextureSizeAlign GPU_TextureSizeAlign;
struct GPU_TextureSizeAlign {
    U64 size;
    U64 align;
};

typedef struct GPU_RasterDesc GPU_RasterDesc;
struct GPU_RasterDesc {
    GPU_CullMode cull_mode;
    B32 wireframe;
    GPU_Format color_format; // 0 = default RGBA8_UNorm
    GPU_Format depth_format; // 0 = default D32_Float
};

typedef struct GPU_BlendDesc GPU_BlendDesc;
struct GPU_BlendDesc {
    B32 enable;
    // NOTE(sa): In the "No Graphics API" philosophy, desktop GPUs set blend
    // state dynamically. Mobile GPUs should use framebuffer fetch intrinsics
    // in the pixel shader for programmable blending.
    U32 src_color;      // maps to VkBlendFactor
    U32 dst_color;
    U32 color_op;       // maps to VkBlendOp
    U32 src_alpha;
    U32 dst_alpha;
    U32 alpha_op;
};

typedef struct GPU_UVec3 GPU_UVec3;
struct GPU_UVec3 {
    U32 x, y, z;
};

////////////////////////////////
//~ sa: Descriptor Blob
//
// On virtually all modern GPUs, a texture descriptor is 256 bits (32 bytes).
// The descriptor heap is simply a homogeneous array of these blobs.

typedef struct GPU_DescriptorBlob GPU_DescriptorBlob;
struct GPU_DescriptorBlob {
    U64 data[4];
};

////////////////////////////////
//~ sa: Device Lifetime

GPU_API GPU_Device *gpu_device_create(GPU_DeviceDesc *desc);
GPU_API void        gpu_device_destroy(GPU_Device *device);

////////////////////////////////
//~ sa: Memory Allocation (CUDA-style gpuMalloc/gpuFree)
//
// Returns a GPU_Alloc with both CPU-side and GPU-side virtual addresses.
// - DEFAULT: CPU can write directly, GPU reads. (Write-combined / UMA / ReBAR)
// - GPU_ONLY: Private VRAM. CPU cannot access. Must upload via copy commands.
// - READBACK: GPU writes, CPU reads back (cached).

GPU_API GPU_Alloc  *gpu_malloc(GPU_Device *device, U64 size, GPU_MemoryKind kind);
GPU_API GPU_Alloc  *gpu_malloc_aligned(GPU_Device *device, U64 size, U64 align, GPU_MemoryKind kind);
GPU_API void        gpu_free(GPU_Device *device, GPU_Alloc *alloc);
GPU_API void       *gpu_alloc_cpu_ptr(GPU_Alloc *alloc);        // NULL for GPU_ONLY
GPU_API U64         gpu_alloc_device_addr(GPU_Alloc *alloc);     // VkDeviceAddress (64-bit GPU VA)
GPU_API U64         gpu_alloc_size(GPU_Alloc *alloc);

////////////////////////////////
//~ sa: Host-to-Device Pointer Mapping
//
// Given a CPU-side pointer into a DEFAULT allocation, returns the
// corresponding GPU virtual address. Called once per allocation, cached.

GPU_API U64 gpu_host_to_device_ptr(GPU_Device *device, GPU_Alloc *alloc, void *cpu_ptr);

////////////////////////////////
//~ sa: Textures & Descriptors

GPU_API GPU_TextureSizeAlign gpu_texture_size_align(GPU_Device *device, GPU_TextureDesc *desc);
GPU_API GPU_Texture         *gpu_texture_create(GPU_Device *device, GPU_TextureDesc *desc, GPU_Alloc *memory);
GPU_API void                 gpu_texture_destroy(GPU_Device *device, GPU_Texture *texture);
GPU_API GPU_DescriptorBlob   gpu_texture_descriptor_blob(GPU_Device *device, GPU_Texture *texture);

////////////////////////////////
//~ sa: Dynamic State Objects

GPU_API GPU_BlendState        *gpu_blend_state_create(GPU_Device *device, GPU_BlendDesc *desc);
GPU_API void                   gpu_blend_state_destroy(GPU_Device *device, GPU_BlendState *state);

GPU_API GPU_DepthStencilState *gpu_depth_stencil_state_create(GPU_Device *device, U32 depth_flags);
GPU_API void                   gpu_depth_stencil_state_destroy(GPU_Device *device, GPU_DepthStencilState *state);

////////////////////////////////
//~ sa: Pipelines (Shader Objects)
//
// Pipelines are simplified: no monolithic PSOs. Just shader IR + minimal
// raster config. Shader IR = SPIR-V bytecode.

GPU_API GPU_Pipeline *gpu_pipeline_compute_create(GPU_Device *device, const U8 *spirv, U64 spirv_size);
GPU_API GPU_Pipeline *gpu_pipeline_graphics_create(GPU_Device *device,
                                                    const U8 *vert_spirv, U64 vert_spirv_size,
                                                    const U8 *frag_spirv, U64 frag_spirv_size,
                                                    GPU_RasterDesc *raster_desc);
GPU_API void          gpu_pipeline_destroy(GPU_Device *device, GPU_Pipeline *pipeline);

////////////////////////////////
//~ sa: Queues

GPU_API GPU_Queue *gpu_queue_create(GPU_Device *device);
GPU_API void       gpu_queue_destroy(GPU_Device *device, GPU_Queue *queue);

////////////////////////////////
//~ sa: Semaphores (Timeline)
//
// All CPU-GPU synchronization uses 64-bit monotonically increasing
// timeline semaphores. No fences, no events, no legacy sync primitives.

GPU_API GPU_Semaphore *gpu_semaphore_create(GPU_Device *device, U64 initial_value);
GPU_API void           gpu_semaphore_destroy(GPU_Device *device, GPU_Semaphore *sem);
GPU_API void           gpu_semaphore_wait(GPU_Device *device, GPU_Semaphore *sem, U64 value);
GPU_API U64            gpu_semaphore_query(GPU_Device *device, GPU_Semaphore *sem);

////////////////////////////////
//~ sa: Command Buffer Recording
//
// Command buffers are strictly transient: allocated immediately before
// recording and discarded after submission. No pooling, no reuse.

GPU_API GPU_CmdBuf *gpu_cmd_begin(GPU_Device *device, GPU_Queue *queue);

// Pipeline & Dynamic State
GPU_API void gpu_cmd_set_pipeline(GPU_CmdBuf *cb, GPU_Pipeline *pipeline);
GPU_API void gpu_cmd_set_blend_state(GPU_CmdBuf *cb, GPU_BlendState *state);
GPU_API void gpu_cmd_set_depth_stencil_state(GPU_CmdBuf *cb, GPU_DepthStencilState *state);
GPU_API void gpu_cmd_set_viewport(GPU_CmdBuf *cb, F32 x, F32 y, F32 w, F32 h, F32 min_depth, F32 max_depth);
GPU_API void gpu_cmd_set_scissor(GPU_CmdBuf *cb, S32 x, S32 y, U32 w, U32 h);

// Render Target Setup
GPU_API void gpu_cmd_begin_rendering(GPU_CmdBuf *cb,
                                      GPU_Texture *color_target,
                                      GPU_Texture *depth_target,
                                      U32 width, U32 height);
GPU_API void gpu_cmd_end_rendering(GPU_CmdBuf *cb);

// Compute Dispatch
GPU_API void gpu_cmd_dispatch(GPU_CmdBuf *cb, U64 data_gpu, GPU_UVec3 grid);
GPU_API void gpu_cmd_dispatch_indirect(GPU_CmdBuf *cb, U64 data_gpu, U64 grid_args_gpu);

// Draw Calls - Single 64-bit root pointer per stage (vertex + pixel)
GPU_API void gpu_cmd_draw(GPU_CmdBuf *cb,
                          U64 vertex_data_gpu,
                          U64 pixel_data_gpu,
                          U32 vertex_count,
                          U32 instance_count);

GPU_API void gpu_cmd_draw_indexed(GPU_CmdBuf *cb,
                                   U64 vertex_data_gpu,
                                   U64 pixel_data_gpu,
                                   U64 index_buffer_gpu,
                                   U32 index_count,
                                   U32 instance_count);

GPU_API void gpu_cmd_draw_indexed_indirect(GPU_CmdBuf *cb,
                                            U64 vertex_data_gpu,
                                            U64 pixel_data_gpu,
                                            U64 indirect_args_gpu);

GPU_API void gpu_cmd_draw_indexed_indirect_count(GPU_CmdBuf *cb,
                                                  U64 vertex_data_gpu,
                                                  U64 pixel_data_gpu,
                                                  U64 indirect_args_gpu,
                                                  U64 count_gpu,
                                                  U32 max_draw_count);

// Memory Commands
GPU_API void gpu_cmd_copy(GPU_CmdBuf *cb, U64 dst_gpu, U64 src_gpu, U64 size);
GPU_API void gpu_cmd_copy_to_texture(GPU_CmdBuf *cb, GPU_Texture *dst, GPU_Alloc *src_upload);
GPU_API void gpu_cmd_copy_texture_to_buffer(GPU_CmdBuf *cb, GPU_Alloc *dst_buffer, GPU_Texture *src_texture);

// Barriers - Coarse-grained queue execution dependencies
// No per-resource state tracking. Just stage -> stage + hazard hints.
GPU_API void gpu_cmd_barrier(GPU_CmdBuf *cb,
                              U32 src_stage_mask,
                              U32 dst_stage_mask,
                              U32 hazard_mask);

////////////////////////////////
//~ sa: Submission

GPU_API void gpu_submit(GPU_Device *device,
                         GPU_Queue *queue,
                         GPU_CmdBuf **cmd_bufs, U32 cmd_buf_count,
                         GPU_Semaphore *signal_sem, U64 signal_value);

GPU_API void gpu_queue_wait_idle(GPU_Device *device, GPU_Queue *queue);
GPU_API void gpu_device_wait_idle(GPU_Device *device);

////////////////////////////////
//~ sa: Window Handle & Swapchain (Cross-Platform)

typedef struct GPU_WindowHandle GPU_WindowHandle;
struct GPU_WindowHandle {
    // Win32
    void *hinstance; // HINSTANCE (optional, NULL defaults to GetModuleHandleA(0))
    void *hwnd;      // HWND
    // Linux / XCB
    void *connection;// xcb_connection_t*
    U32   window;    // xcb_window_t
};

GPU_API GPU_Swapchain *gpu_swapchain_create(GPU_Device *device, const GPU_WindowHandle *window, U32 width, U32 height);
GPU_API GPU_Swapchain *gpu_swapchain_create_win32(GPU_Device *device, void *hinstance, void *hwnd, U32 width, U32 height);
GPU_API GPU_Swapchain *gpu_swapchain_create_xcb(GPU_Device *device, void *connection, U32 window, U32 width, U32 height);
GPU_API void           gpu_swapchain_destroy(GPU_Device *device, GPU_Swapchain *swapchain);
GPU_API GPU_Texture   *gpu_swapchain_acquire(GPU_Device *device, GPU_Swapchain *swapchain);
GPU_API void           gpu_swapchain_submit_and_present(GPU_Device *device, GPU_Queue *queue, GPU_Swapchain *swapchain, GPU_CmdBuf *cb);
GPU_API GPU_Format     gpu_swapchain_format(GPU_Swapchain *swapchain);

#endif // GPU_H

// ============================================================================
//
//                          IMPLEMENTATION
//
// ============================================================================

#ifdef GPU_IMPLEMENTATION
#ifndef GPU_IMPLEMENTATION_GUARD
#define GPU_IMPLEMENTATION_GUARD

#include <string.h>
#include <stdio.h>

#if defined(GPU_OS_WINDOWS)
# ifndef WIN32_LEAN_AND_MEAN
#  define WIN32_LEAN_AND_MEAN
# endif
# ifndef NOMINMAX
#  define NOMINMAX
# endif
# include <windows.h>
#else
# include <dlfcn.h>
#endif

////////////////////////////////
//~ sa: Vulkan Function Pointer Loading (No vulkan.h dependency)
//
// We load Vulkan entirely at runtime via dlopen/dlsym. Zero compile-time
// dependency on the Vulkan SDK. All Vulkan types and function pointers
// are defined locally below.

//- Vulkan Base Types
typedef U32 VkFlags;
typedef U32 VkBool32;
typedef U64 VkFlags64;
typedef U64 VkDeviceSize;
typedef U64 VkDeviceAddress;

//- Vulkan Handle Types (non-dispatchable = U64, dispatchable = pointer)
typedef struct VkInstance_T       *VkInstance;
typedef struct VkPhysicalDevice_T *VkPhysicalDevice;
typedef struct VkDevice_T         *VkDevice;
typedef struct VkQueue_T          *VkQueue;
typedef struct VkCommandBuffer_T  *VkCommandBuffer;

// NOTE(sa): Non-dispatchable handles are U64 on all platforms for simplicity
typedef U64 VkSemaphore;
typedef U64 VkFence;
typedef U64 VkDeviceMemory;
typedef U64 VkBuffer;
typedef U64 VkImage;
typedef U64 VkImageView;
typedef U64 VkShaderModule;
typedef U64 VkPipelineLayout;
typedef U64 VkRenderPass;
typedef U64 VkPipeline_Vk;
typedef U64 VkDescriptorSetLayout;
typedef U64 VkCommandPool;
typedef U64 VkSurfaceKHR;
typedef U64 VkSwapchainKHR;
typedef U64 VkDebugUtilsMessengerEXT;
typedef U64 VkSampler;

//- Vulkan Constants
#define VK_NULL_HANDLE 0
#define VK_TRUE  1
#define VK_FALSE 0
#define VK_WHOLE_SIZE (~(U64)0)
#define VK_MAX_EXTENSION_NAME_SIZE 256

//- Vulkan Result
typedef S32 VkResult;
#define VK_SUCCESS                    0
#define VK_NOT_READY                  1
#define VK_TIMEOUT                    2
#define VK_ERROR_OUT_OF_HOST_MEMORY  -1
#define VK_ERROR_OUT_OF_DEVICE_MEMORY -2
#define VK_ERROR_DEVICE_LOST         -4
#define VK_ERROR_LAYER_NOT_PRESENT   -6
#define VK_ERROR_EXTENSION_NOT_PRESENT -7

//- Vulkan Structure Types (sType enum)
typedef S32 VkStructureType;
#define VK_STRUCTURE_TYPE_APPLICATION_INFO                    0
#define VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO                1
#define VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO            2
#define VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO                  3
#define VK_STRUCTURE_TYPE_SUBMIT_INFO                         4
#define VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO                5
#define VK_STRUCTURE_TYPE_FENCE_CREATE_INFO                   8
#define VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO               9
#define VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO                  12
#define VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO                   14
#define VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO              15
#define VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO           16
#define VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO   18
#define VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO 19
#define VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO 20
#define VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO 22
#define VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO 23
#define VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO 24
#define VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO 25
#define VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO 26
#define VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO 27
#define VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO         28
#define VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO       30
#define VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO        29
#define VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO            39
#define VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO        40
#define VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO           42
#define VK_STRUCTURE_TYPE_MEMORY_BARRIER                      46
#define VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER               44
#define VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER                45

// Vulkan 1.2+
#define VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES 49
#define VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES 51
#define VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_PROPERTIES 52
#define VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES 53

// Timeline Semaphore
#define VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO          1000207002
#define VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO      1000207003
#define VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO                 1000207004
#define VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO               1000207005

// Buffer Device Address
#define VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES 1000257000
#define VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO          1000244001
#define VK_STRUCTURE_TYPE_BUFFER_OPAQUE_CAPTURE_ADDRESS_CREATE_INFO 1000257002
#define VK_STRUCTURE_TYPE_MEMORY_OPAQUE_CAPTURE_ADDRESS_ALLOCATE_INFO 1000257003

// Dynamic Rendering (Vulkan 1.3)
#define VK_STRUCTURE_TYPE_RENDERING_INFO                      1000044000
#define VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO           1000044001
#define VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES 1000044003

// Push Constants replacement: push descriptors via push constants
#define VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2          1000059000
#define VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2        1000059001
#define VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2 1000059006

// Synchronization2
#define VK_STRUCTURE_TYPE_MEMORY_BARRIER_2                    1000314000
#define VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER_2             1000314001
#define VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2              1000314002
#define VK_STRUCTURE_TYPE_DEPENDENCY_INFO                     1000314003
#define VK_STRUCTURE_TYPE_SUBMIT_INFO_2                       1000314004
#define VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO          1000314006
#define VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO               1000314005
#define VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SYNCHRONIZATION_2_FEATURES 1000314007

//- Vulkan Enums
#define VK_API_VERSION_1_3       ((U32)(1) << 22 | (U32)(3) << 12)

#define VK_BUFFER_USAGE_TRANSFER_SRC_BIT      0x00000001
#define VK_BUFFER_USAGE_TRANSFER_DST_BIT      0x00000002
#define VK_BUFFER_USAGE_STORAGE_BUFFER_BIT    0x00000020
#define VK_BUFFER_USAGE_INDEX_BUFFER_BIT      0x00000040
#define VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT   0x00000100
#define VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT 0x00020000

#define VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT   0x00000001
#define VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT   0x00000002
#define VK_MEMORY_PROPERTY_HOST_COHERENT_BIT  0x00000004
#define VK_MEMORY_PROPERTY_HOST_CACHED_BIT    0x00000008

#define VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT 0x00000002

#define VK_SHARING_MODE_EXCLUSIVE 0
#define VK_COMMAND_POOL_CREATE_TRANSIENT_BIT          0x00000001
#define VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT 0x00000002
#define VK_COMMAND_BUFFER_LEVEL_PRIMARY 0
#define VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT 0x00000001

#define VK_IMAGE_TYPE_2D           1
#define VK_IMAGE_TILING_OPTIMAL    0
#define VK_IMAGE_USAGE_TRANSFER_DST_BIT        0x00000002
#define VK_IMAGE_USAGE_SAMPLED_BIT             0x00000004
#define VK_IMAGE_USAGE_STORAGE_BIT             0x00000008
#define VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT    0x00000010
#define VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT 0x00000020
#define VK_IMAGE_USAGE_TRANSFER_SRC_BIT        0x00000001

#define VK_SAMPLE_COUNT_1_BIT     0x00000001
#define VK_IMAGE_LAYOUT_UNDEFINED 0
#define VK_IMAGE_LAYOUT_GENERAL   1
#define VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL 2
#define VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL 3
#define VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL 5
#define VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL 6
#define VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL 7
#define VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL 1000314001
#define VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL  1000314000

#define VK_IMAGE_VIEW_TYPE_2D   1
#define VK_COMPONENT_SWIZZLE_IDENTITY 0

#define VK_IMAGE_ASPECT_COLOR_BIT   0x00000001
#define VK_IMAGE_ASPECT_DEPTH_BIT   0x00000002
#define VK_IMAGE_ASPECT_STENCIL_BIT 0x00000004

#define VK_PIPELINE_BIND_POINT_COMPUTE  1
#define VK_PIPELINE_BIND_POINT_GRAPHICS 0

#define VK_SHADER_STAGE_VERTEX_BIT    0x00000001
#define VK_SHADER_STAGE_FRAGMENT_BIT  0x00000010
#define VK_SHADER_STAGE_COMPUTE_BIT   0x00000020
#define VK_SHADER_STAGE_ALL_GRAPHICS  0x0000001F
#define VK_SHADER_STAGE_ALL           0x7FFFFFFF

#define VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST 3
#define VK_POLYGON_MODE_FILL     0
#define VK_POLYGON_MODE_LINE     1
#define VK_FRONT_FACE_COUNTER_CLOCKWISE 0
#define VK_FRONT_FACE_CLOCKWISE  1
#define VK_CULL_MODE_NONE        0
#define VK_CULL_MODE_FRONT_BIT   0x00000001
#define VK_CULL_MODE_BACK_BIT    0x00000002

#define VK_COMPARE_OP_LESS          4
#define VK_COMPARE_OP_LESS_OR_EQUAL 5
#define VK_COMPARE_OP_ALWAYS        7

#define VK_DYNAMIC_STATE_VIEWPORT            0
#define VK_DYNAMIC_STATE_SCISSOR             1
#define VK_DYNAMIC_STATE_BLEND_CONSTANTS     12
#define VK_DYNAMIC_STATE_DEPTH_BIAS          3
#define VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE   1000267009
#define VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE  1000267010
#define VK_DYNAMIC_STATE_DEPTH_COMPARE_OP    1000267011

#define VK_COLOR_COMPONENT_R_BIT 0x00000001
#define VK_COLOR_COMPONENT_G_BIT 0x00000002
#define VK_COLOR_COMPONENT_B_BIT 0x00000004
#define VK_COLOR_COMPONENT_A_BIT 0x00000008

#define VK_BLEND_FACTOR_ZERO             0
#define VK_BLEND_FACTOR_ONE              1
#define VK_BLEND_FACTOR_SRC_ALPHA        6
#define VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA 7
#define VK_BLEND_OP_ADD                  0

#define VK_INDEX_TYPE_UINT16 0
#define VK_INDEX_TYPE_UINT32 1

#define VK_SEMAPHORE_TYPE_TIMELINE 1

#define VK_FORMAT_UNDEFINED                0
#define VK_FORMAT_R8_UNORM                 9
#define VK_FORMAT_R8G8_UNORM               16
#define VK_FORMAT_R8G8B8A8_UNORM           37
#define VK_FORMAT_R8G8B8A8_SRGB            43
#define VK_FORMAT_B8G8R8A8_UNORM           44
#define VK_FORMAT_B8G8R8A8_SRGB            50
#define VK_FORMAT_R16_SFLOAT               76
#define VK_FORMAT_R16G16_SFLOAT            83
#define VK_FORMAT_R16G16B16A16_SFLOAT      97
#define VK_FORMAT_R32_SFLOAT               100
#define VK_FORMAT_R32G32_SFLOAT            103
#define VK_FORMAT_R32G32B32A32_SFLOAT      109
#define VK_FORMAT_R32_UINT                 98
#define VK_FORMAT_R16_UINT                 74
#define VK_FORMAT_D16_UNORM                124
#define VK_FORMAT_D24_UNORM_S8_UINT        129
#define VK_FORMAT_D32_SFLOAT               126
#define VK_FORMAT_D32_SFLOAT_S8_UINT       130

// Pipeline stage flags 2 (VkPipelineStageFlagBits2)
#define VK_PIPELINE_STAGE_2_NONE                     ((VkFlags64)0)
#define VK_PIPELINE_STAGE_2_TOP_OF_PIPE_BIT          ((VkFlags64)0x00000001)
#define VK_PIPELINE_STAGE_2_BOTTOM_OF_PIPE_BIT       ((VkFlags64)0x00002000)
#define VK_PIPELINE_STAGE_2_TRANSFER_BIT             ((VkFlags64)0x00001000)
#define VK_PIPELINE_STAGE_2_COMPUTE_SHADER_BIT       ((VkFlags64)0x00000800)
#define VK_PIPELINE_STAGE_2_VERTEX_SHADER_BIT        ((VkFlags64)0x00000008)
#define VK_PIPELINE_STAGE_2_FRAGMENT_SHADER_BIT      ((VkFlags64)0x00000080)
#define VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT ((VkFlags64)0x00000400)
#define VK_PIPELINE_STAGE_2_EARLY_FRAGMENT_TESTS_BIT ((VkFlags64)0x00000100)
#define VK_PIPELINE_STAGE_2_LATE_FRAGMENT_TESTS_BIT  ((VkFlags64)0x00000200)
#define VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT         ((VkFlags64)0x00010000)
#define VK_PIPELINE_STAGE_2_DRAW_INDIRECT_BIT        ((VkFlags64)0x00000002)

// Access flags 2 (VkAccessFlagBits2)
#define VK_ACCESS_2_NONE                             ((VkFlags64)0)
#define VK_ACCESS_2_MEMORY_READ_BIT                  ((VkFlags64)0x00008000)
#define VK_ACCESS_2_MEMORY_WRITE_BIT                 ((VkFlags64)0x00010000)
#define VK_ACCESS_2_TRANSFER_READ_BIT                ((VkFlags64)0x00000800)
#define VK_ACCESS_2_TRANSFER_WRITE_BIT               ((VkFlags64)0x00001000)
#define VK_ACCESS_2_SHADER_READ_BIT                  ((VkFlags64)0x00000020)
#define VK_ACCESS_2_SHADER_WRITE_BIT                 ((VkFlags64)0x00000040)
#define VK_ACCESS_2_COLOR_ATTACHMENT_READ_BIT        ((VkFlags64)0x00000080)
#define VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT       ((VkFlags64)0x00000100)
#define VK_ACCESS_2_DEPTH_STENCIL_ATTACHMENT_READ_BIT ((VkFlags64)0x00000200)
#define VK_ACCESS_2_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT ((VkFlags64)0x00000400)

//- Vulkan Structure Definitions (partial, only what we need)

typedef struct VkExtent2D { U32 width; U32 height; } VkExtent2D;
typedef struct VkExtent3D { U32 width; U32 height; U32 depth; } VkExtent3D;
typedef struct VkOffset2D { S32 x; S32 y; } VkOffset2D;
typedef struct VkRect2D { VkOffset2D offset; VkExtent2D extent; } VkRect2D;
typedef struct VkViewport { F32 x; F32 y; F32 width; F32 height; F32 minDepth; F32 maxDepth; } VkViewport;

typedef struct VkComponentMapping {
    S32 r, g, b, a;
} VkComponentMapping;

typedef struct VkImageSubresourceRange {
    VkFlags aspectMask;
    U32 baseMipLevel;
    U32 levelCount;
    U32 baseArrayLayer;
    U32 layerCount;
} VkImageSubresourceRange;

typedef struct VkImageSubresourceLayers {
    VkFlags aspectMask;
    U32 mipLevel;
    U32 baseArrayLayer;
    U32 layerCount;
} VkImageSubresourceLayers;

typedef struct VkMemoryRequirements {
    VkDeviceSize size;
    VkDeviceSize alignment;
    U32 memoryTypeBits;
} VkMemoryRequirements;

typedef struct VkMemoryType {
    VkFlags propertyFlags;
    U32 heapIndex;
} VkMemoryType;

typedef struct VkMemoryHeap {
    VkDeviceSize size;
    VkFlags flags;
} VkMemoryHeap;

typedef struct VkPhysicalDeviceMemoryProperties {
    U32 memoryTypeCount;
    VkMemoryType memoryTypes[32];
    U32 memoryHeapCount;
    VkMemoryHeap memoryHeaps[16];
} VkPhysicalDeviceMemoryProperties;

typedef struct VkPhysicalDeviceProperties {
    U32 apiVersion;
    U32 driverVersion;
    U32 vendorID;
    U32 deviceID;
    U32 deviceType;
    char deviceName[256];
    U8 pipelineCacheUUID[16];
    // ...remainder omitted for brevity, we only read the above fields
    U8 _padding[2048]; // plenty of room for VkPhysicalDeviceLimits (over 500 bytes) + VkPhysicalDeviceSparseProperties
} VkPhysicalDeviceProperties;

typedef struct VkQueueFamilyProperties {
    VkFlags queueFlags;
    U32 queueCount;
    U32 timestampValidBits;
    VkExtent3D minImageTransferGranularity;
} VkQueueFamilyProperties;

// Rendering attachment info (Vulkan 1.3 dynamic rendering)
typedef struct VkRenderingAttachmentInfo {
    VkStructureType sType;
    const void *pNext;
    U64 imageView; // VkImageView
    S32 imageLayout;
    S32 resolveMode;
    U64 resolveImageView;
    S32 resolveImageLayout;
    S32 loadOp;
    S32 storeOp;
    union {
        F32 float32[4];
        S32 int32[4];
        U32 uint32[4];
    } clearValue;
} VkRenderingAttachmentInfo;

typedef struct VkRenderingInfo {
    VkStructureType sType;
    const void *pNext;
    VkFlags flags;
    VkRect2D renderArea;
    U32 layerCount;
    U32 viewMask;
    U32 colorAttachmentCount;
    const VkRenderingAttachmentInfo *pColorAttachments;
    const VkRenderingAttachmentInfo *pDepthAttachment;
    const VkRenderingAttachmentInfo *pStencilAttachment;
} VkRenderingInfo;

// Memory barrier 2 (Synchronization2)
typedef struct VkMemoryBarrier2 {
    VkStructureType sType;
    const void *pNext;
    VkFlags64 srcStageMask;
    VkFlags64 srcAccessMask;
    VkFlags64 dstStageMask;
    VkFlags64 dstAccessMask;
} VkMemoryBarrier2;

typedef struct VkImageMemoryBarrier2 {
    VkStructureType sType;
    const void *pNext;
    VkFlags64 srcStageMask;
    VkFlags64 srcAccessMask;
    VkFlags64 dstStageMask;
    VkFlags64 dstAccessMask;
    S32 oldLayout;
    S32 newLayout;
    U32 srcQueueFamilyIndex;
    U32 dstQueueFamilyIndex;
    VkImage image;
    VkImageSubresourceRange subresourceRange;
} VkImageMemoryBarrier2;

typedef struct VkDependencyInfo {
    VkStructureType sType;
    const void *pNext;
    VkFlags dependencyFlags;
    U32 memoryBarrierCount;
    const VkMemoryBarrier2 *pMemoryBarriers;
    U32 bufferMemoryBarrierCount;
    const void *pBufferMemoryBarriers;
    U32 imageMemoryBarrierCount;
    const VkImageMemoryBarrier2 *pImageMemoryBarriers;
} VkDependencyInfo;

// Submit info 2 (Synchronization2)
typedef struct VkSemaphoreSubmitInfo {
    VkStructureType sType;
    const void *pNext;
    VkSemaphore semaphore;
    U64 value;
    VkFlags64 stageMask;
    U32 deviceIndex;
} VkSemaphoreSubmitInfo;

typedef struct VkCommandBufferSubmitInfo {
    VkStructureType sType;
    const void *pNext;
    VkCommandBuffer commandBuffer;
    U32 deviceMask;
} VkCommandBufferSubmitInfo;

typedef struct VkSubmitInfo2 {
    VkStructureType sType;
    const void *pNext;
    VkFlags flags;
    U32 waitSemaphoreInfoCount;
    const VkSemaphoreSubmitInfo *pWaitSemaphoreInfos;
    U32 commandBufferInfoCount;
    const VkCommandBufferSubmitInfo *pCommandBufferInfos;
    U32 signalSemaphoreInfoCount;
    const VkSemaphoreSubmitInfo *pSignalSemaphoreInfos;
} VkSubmitInfo2;

typedef struct VkBufferCopy { U64 srcOffset; U64 dstOffset; U64 size; } VkBufferCopy;
typedef struct VkBufferImageCopy {
    U64 bufferOffset;
    U32 bufferRowLength;
    U32 bufferImageHeight;
    VkImageSubresourceLayers imageSubresource;
    struct { S32 x, y, z; } imageOffset;
    VkExtent3D imageExtent;
} VkBufferImageCopy;

////////////////////////////////
//~ sa: Vulkan Function Pointer Table

typedef void (GPU_VK_CALL *PFN_vkVoidFunction)(void);
typedef PFN_vkVoidFunction (GPU_VK_CALL *PFN_vkGetInstanceProcAddr)(VkInstance, const char*);

// NOTE(sa): We store all Vulkan function pointers in a single struct.
// Loaded once at device creation time via vkGetInstanceProcAddr / vkGetDeviceProcAddr.
typedef struct GPU_VkFunctions GPU_VkFunctions;
struct GPU_VkFunctions {
    // Instance
    VkResult (*vkCreateInstance)(const void*, const void*, VkInstance*);
    void     (*vkDestroyInstance)(VkInstance, const void*);
    VkResult (*vkEnumeratePhysicalDevices)(VkInstance, U32*, VkPhysicalDevice*);
    void     (*vkGetPhysicalDeviceProperties)(VkPhysicalDevice, VkPhysicalDeviceProperties*);
    void     (*vkGetPhysicalDeviceMemoryProperties)(VkPhysicalDevice, VkPhysicalDeviceMemoryProperties*);
    void     (*vkGetPhysicalDeviceQueueFamilyProperties)(VkPhysicalDevice, U32*, VkQueueFamilyProperties*);

    // Device
    VkResult (*vkCreateDevice)(VkPhysicalDevice, const void*, const void*, VkDevice*);
    void     (*vkDestroyDevice)(VkDevice, const void*);
    void     (*vkGetDeviceQueue)(VkDevice, U32, U32, VkQueue*);
    VkResult (*vkDeviceWaitIdle)(VkDevice);
    VkResult (*vkQueueWaitIdle)(VkQueue);
    PFN_vkVoidFunction (*vkGetDeviceProcAddr)(VkDevice, const char*);

    // Memory
    VkResult (*vkAllocateMemory)(VkDevice, const void*, const void*, VkDeviceMemory*);
    void     (*vkFreeMemory)(VkDevice, VkDeviceMemory, const void*);
    VkResult (*vkMapMemory)(VkDevice, VkDeviceMemory, U64, U64, U32, void**);
    void     (*vkUnmapMemory)(VkDevice, VkDeviceMemory);
    void     (*vkGetBufferMemoryRequirements)(VkDevice, VkBuffer, VkMemoryRequirements*);
    void     (*vkGetImageMemoryRequirements)(VkDevice, VkImage, VkMemoryRequirements*);
    VkResult (*vkBindBufferMemory)(VkDevice, VkBuffer, VkDeviceMemory, U64);
    VkResult (*vkBindImageMemory)(VkDevice, VkImage, VkDeviceMemory, U64);

    // Buffer
    VkResult (*vkCreateBuffer)(VkDevice, const void*, const void*, VkBuffer*);
    void     (*vkDestroyBuffer)(VkDevice, VkBuffer, const void*);
    VkDeviceAddress (*vkGetBufferDeviceAddress)(VkDevice, const void*);

    // Image
    VkResult (*vkCreateImage)(VkDevice, const void*, const void*, VkImage*);
    void     (*vkDestroyImage)(VkDevice, VkImage, const void*);
    VkResult (*vkCreateImageView)(VkDevice, const void*, const void*, U64*);
    void     (*vkDestroyImageView)(VkDevice, U64, const void*);

    // Pipeline
    VkResult (*vkCreateShaderModule)(VkDevice, const void*, const void*, VkShaderModule*);
    void     (*vkDestroyShaderModule)(VkDevice, VkShaderModule, const void*);
    VkResult (*vkCreatePipelineLayout)(VkDevice, const void*, const void*, VkPipelineLayout*);
    void     (*vkDestroyPipelineLayout)(VkDevice, VkPipelineLayout, const void*);
    VkResult (*vkCreateGraphicsPipelines)(VkDevice, U64, U32, const void*, const void*, VkPipeline_Vk*);
    VkResult (*vkCreateComputePipelines)(VkDevice, U64, U32, const void*, const void*, VkPipeline_Vk*);
    void     (*vkDestroyPipeline)(VkDevice, VkPipeline_Vk, const void*);

    // Command Pool & Buffer
    VkResult (*vkCreateCommandPool)(VkDevice, const void*, const void*, VkCommandPool*);
    void     (*vkDestroyCommandPool)(VkDevice, VkCommandPool, const void*);
    VkResult (*vkAllocateCommandBuffers)(VkDevice, const void*, VkCommandBuffer*);
    void     (*vkFreeCommandBuffers)(VkDevice, VkCommandPool, U32, const VkCommandBuffer*);
    VkResult (*vkBeginCommandBuffer)(VkCommandBuffer, const void*);
    VkResult (*vkEndCommandBuffer)(VkCommandBuffer);
    VkResult (*vkResetCommandPool)(VkDevice, VkCommandPool, VkFlags);

    // Commands
    void (*vkCmdBindPipeline)(VkCommandBuffer, S32, VkPipeline_Vk);
    void (*vkCmdPushConstants)(VkCommandBuffer, VkPipelineLayout, VkFlags, U32, U32, const void*);
    void (*vkCmdSetViewport)(VkCommandBuffer, U32, U32, const VkViewport*);
    void (*vkCmdSetScissor)(VkCommandBuffer, U32, U32, const VkRect2D*);
    void (*vkCmdDraw)(VkCommandBuffer, U32, U32, U32, U32);
    void (*vkCmdDrawIndexed)(VkCommandBuffer, U32, U32, U32, S32, U32);
    void (*vkCmdDrawIndirect)(VkCommandBuffer, VkBuffer, U64, U32, U32);
    void (*vkCmdDrawIndexedIndirect)(VkCommandBuffer, VkBuffer, U64, U32, U32);
    void (*vkCmdDrawIndexedIndirectCount)(VkCommandBuffer, VkBuffer, U64, VkBuffer, U64, U32, U32);
    void (*vkCmdDispatch)(VkCommandBuffer, U32, U32, U32);
    void (*vkCmdDispatchIndirect)(VkCommandBuffer, VkBuffer, U64);
    void (*vkCmdBindIndexBuffer)(VkCommandBuffer, VkBuffer, U64, S32);
    void (*vkCmdCopyBuffer)(VkCommandBuffer, VkBuffer, VkBuffer, U32, const VkBufferCopy*);
    void (*vkCmdCopyBufferToImage)(VkCommandBuffer, VkBuffer, VkImage, S32, U32, const VkBufferImageCopy*);
    void (*vkCmdCopyImageToBuffer)(VkCommandBuffer, VkImage, S32, VkBuffer, U32, const VkBufferImageCopy*);

    // Dynamic Rendering (Vulkan 1.3)
    void (*vkCmdBeginRendering)(VkCommandBuffer, const VkRenderingInfo*);
    void (*vkCmdEndRendering)(VkCommandBuffer);

    // Synchronization2 (Vulkan 1.3)
    void (*vkCmdPipelineBarrier2)(VkCommandBuffer, const VkDependencyInfo*);
    VkResult (*vkQueueSubmit2)(VkQueue, U32, const VkSubmitInfo2*, VkFence);

    // Semaphore
    VkResult (*vkCreateSemaphore)(VkDevice, const void*, const void*, VkSemaphore*);
    void     (*vkDestroySemaphore)(VkDevice, VkSemaphore, const void*);
    VkResult (*vkWaitSemaphores)(VkDevice, const void*, U64);
    VkResult (*vkGetSemaphoreCounterValue)(VkDevice, VkSemaphore, U64*);
    VkResult (*vkSignalSemaphore)(VkDevice, const void*);

    // Fence
    VkResult (*vkCreateFence)(VkDevice, const void*, const void*, VkFence*);
    void     (*vkDestroyFence)(VkDevice, VkFence, const void*);
    VkResult (*vkWaitForFences)(VkDevice, U32, const VkFence*, VkBool32, U64);
    VkResult (*vkResetFences)(VkDevice, U32, const VkFence*);

    // Dynamic State (Vulkan 1.3)
    void (*vkCmdSetDepthTestEnable)(VkCommandBuffer, VkBool32);
    void (*vkCmdSetDepthWriteEnable)(VkCommandBuffer, VkBool32);
    void (*vkCmdSetDepthCompareOp)(VkCommandBuffer, S32);

    // Surface & Swapchain (Vulkan WSI)
    VkResult (*vkCreateXcbSurfaceKHR)(VkInstance, const void*, const void*, VkSurfaceKHR*);
    VkResult (*vkCreateWin32SurfaceKHR)(VkInstance, const void*, const void*, VkSurfaceKHR*);
    void     (*vkDestroySurfaceKHR)(VkInstance, VkSurfaceKHR, const void*);
    VkResult (*vkGetPhysicalDeviceSurfaceSupportKHR)(VkPhysicalDevice, U32, VkSurfaceKHR, VkBool32*);
    VkResult (*vkGetPhysicalDeviceSurfaceCapabilitiesKHR)(VkPhysicalDevice, VkSurfaceKHR, void*);
    VkResult (*vkGetPhysicalDeviceSurfaceFormatsKHR)(VkPhysicalDevice, VkSurfaceKHR, U32*, void*);
    VkResult (*vkGetPhysicalDeviceSurfacePresentModesKHR)(VkPhysicalDevice, VkSurfaceKHR, U32*, S32*);
    VkResult (*vkCreateSwapchainKHR)(VkDevice, const void*, const void*, VkSwapchainKHR*);
    void     (*vkDestroySwapchainKHR)(VkDevice, VkSwapchainKHR, const void*);
    VkResult (*vkGetSwapchainImagesKHR)(VkDevice, VkSwapchainKHR, U32*, VkImage*);
    VkResult (*vkAcquireNextImageKHR)(VkDevice, VkSwapchainKHR, U64, VkSemaphore, VkFence, U32*);
    VkResult (*vkQueuePresentKHR)(VkQueue, const void*);
};

////////////////////////////////
//~ sa: Internal Structures

struct GPU_Swapchain {
    GPU_Device *device;
    VkSurfaceKHR surface;
    VkSwapchainKHR swapchain;
    U32 image_count;
    GPU_Texture *textures[8];
    VkSemaphore image_available_sems[8];
    VkSemaphore render_finished_sems[8];
    VkFence in_flight_fences[8];
    GPU_CmdBuf *frame_cmd_bufs[8];
    U32 current_image_index;
    U32 current_frame;
    U32 width;
    U32 height;
    GPU_Format format;
};

struct GPU_Device {
    void *vk_lib;
    VkInstance instance;
    VkPhysicalDevice physical_device;
    VkDevice device;
    VkPhysicalDeviceMemoryProperties mem_props;
    U32 graphics_queue_family;
    U32 compute_queue_family;
    U32 transfer_queue_family;
    VkPipelineLayout push_constant_layout;  // shared layout: 2x U64 push constants
    GPU_VkFunctions vk;
    B32 validation_enabled;
    B32 surface_enabled;
};

struct GPU_Alloc {
    VkBuffer buffer;
    VkDeviceMemory memory;
    void *cpu_ptr;           // NULL for GPU_ONLY
    VkDeviceAddress device_addr;
    U64 size;
    GPU_MemoryKind kind;
};

struct GPU_Texture {
    VkImage image;
    VkDeviceMemory memory;
    U64 image_view;         // VkImageView
    GPU_TextureDesc desc;
    B32 owns_memory;        // did we allocate the VkDeviceMemory?
};

struct GPU_Pipeline {
    VkPipeline_Vk pipeline;
    S32 bind_point;         // VK_PIPELINE_BIND_POINT_GRAPHICS or _COMPUTE
    VkPipelineLayout layout;
};

struct GPU_DepthStencilState {
    B32 depth_test_enable;
    B32 depth_write_enable;
    S32 compare_op;
};

struct GPU_BlendState {
    GPU_BlendDesc desc;
};

struct GPU_Queue {
    VkQueue vk_queue;
    U32 family_index;
    VkCommandPool cmd_pool;
};

struct GPU_CmdBuf {
    VkCommandBuffer vk_cb;
    GPU_Queue *queue;
    GPU_Device *device;
    VkPipelineLayout bound_layout;
};

struct GPU_Semaphore {
    VkSemaphore vk_sem;
};

////////////////////////////////
//~ sa: Vulkan Format Conversion

internal S32
gpu__vk_format(GPU_Format fmt)
{
    switch (fmt) {
        case GPU_Format_R8_UNorm:             return VK_FORMAT_R8_UNORM;
        case GPU_Format_R8G8_UNorm:           return VK_FORMAT_R8G8_UNORM;
        case GPU_Format_R8G8B8A8_UNorm:       return VK_FORMAT_R8G8B8A8_UNORM;
        case GPU_Format_R8G8B8A8_SRGB:        return VK_FORMAT_R8G8B8A8_SRGB;
        case GPU_Format_B8G8R8A8_UNorm:       return VK_FORMAT_B8G8R8A8_UNORM;
        case GPU_Format_B8G8R8A8_SRGB:        return VK_FORMAT_B8G8R8A8_SRGB;
        case GPU_Format_R16_Float:            return VK_FORMAT_R16_SFLOAT;
        case GPU_Format_R16G16_Float:         return VK_FORMAT_R16G16_SFLOAT;
        case GPU_Format_R16G16B16A16_Float:   return VK_FORMAT_R16G16B16A16_SFLOAT;
        case GPU_Format_R32_Float:            return VK_FORMAT_R32_SFLOAT;
        case GPU_Format_R32G32_Float:         return VK_FORMAT_R32G32_SFLOAT;
        case GPU_Format_R32G32B32A32_Float:   return VK_FORMAT_R32G32B32A32_SFLOAT;
        case GPU_Format_R32_UInt:             return VK_FORMAT_R32_UINT;
        case GPU_Format_R16_UInt:             return VK_FORMAT_R16_UINT;
        case GPU_Format_D16_UNorm:            return VK_FORMAT_D16_UNORM;
        case GPU_Format_D24_UNorm_S8_UInt:    return VK_FORMAT_D24_UNORM_S8_UINT;
        case GPU_Format_D32_Float:            return VK_FORMAT_D32_SFLOAT;
        case GPU_Format_D32_Float_S8_UInt:    return VK_FORMAT_D32_SFLOAT_S8_UINT;
        default:                              return VK_FORMAT_UNDEFINED;
    }
}

internal B32
gpu__format_is_depth(GPU_Format fmt)
{
    return (fmt == GPU_Format_D16_UNorm ||
            fmt == GPU_Format_D24_UNorm_S8_UInt ||
            fmt == GPU_Format_D32_Float ||
            fmt == GPU_Format_D32_Float_S8_UInt);
}

////////////////////////////////
//~ sa: Vulkan Stage Mask Conversion

internal VkFlags64
gpu__vk_stage_mask(U32 stage_flags)
{
    VkFlags64 result = VK_PIPELINE_STAGE_2_NONE;
    if (stage_flags & GPU_StageFlags_Transfer)       result |= VK_PIPELINE_STAGE_2_TRANSFER_BIT;
    if (stage_flags & GPU_StageFlags_Compute)        result |= VK_PIPELINE_STAGE_2_COMPUTE_SHADER_BIT;
    if (stage_flags & GPU_StageFlags_VertexShader)   result |= VK_PIPELINE_STAGE_2_VERTEX_SHADER_BIT;
    if (stage_flags & GPU_StageFlags_PixelShader)    result |= VK_PIPELINE_STAGE_2_FRAGMENT_SHADER_BIT;
    if (stage_flags & GPU_StageFlags_RasterColorOut) result |= VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;
    if (stage_flags & GPU_StageFlags_RasterDepthOut) result |= (VK_PIPELINE_STAGE_2_EARLY_FRAGMENT_TESTS_BIT |
                                                                VK_PIPELINE_STAGE_2_LATE_FRAGMENT_TESTS_BIT);
    if (stage_flags == GPU_StageFlags_All)           result = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
    return result;
}

////////////////////////////////
//~ sa: Memory Type Finder

internal S32
gpu__find_memory_type(GPU_Device *dev, U32 type_bits, VkFlags required_props)
{
    for (U32 i = 0; i < dev->mem_props.memoryTypeCount; i += 1) {
        if ((type_bits & (1u << i)) &&
            (dev->mem_props.memoryTypes[i].propertyFlags & required_props) == required_props) {
            return (S32)i;
        }
    }
    return -1;
}

////////////////////////////////
//~ sa: Vulkan Function Loader

// NOTE(sa): Vulkan function pointers are loaded via vkGetInstanceProcAddr /
// vkGetDeviceProcAddr which return PFN_vkVoidFunction. We use a union-based
// cast to satisfy strict ISO C (which forbids function pointer <-> void* casts).
// This is the standard portable pattern used by Vulkan loaders.

#define GPU__LOAD_INSTANCE_FN(fn) do { \
    union { PFN_vkVoidFunction vk; __typeof__(dev->vk.fn) typed; } gpu__u; \
    gpu__u.vk = get_instance_proc(dev->instance, #fn); \
    dev->vk.fn = gpu__u.typed; \
    GPU_ASSERT(dev->vk.fn != 0); \
} while(0)

#define GPU__LOAD_DEVICE_FN(fn) do { \
    union { PFN_vkVoidFunction vk; __typeof__(dev->vk.fn) typed; } gpu__u; \
    gpu__u.vk = dev->vk.vkGetDeviceProcAddr(dev->device, #fn); \
    dev->vk.fn = gpu__u.typed; \
    GPU_ASSERT(dev->vk.fn != 0); \
} while(0)

// NOTE(sa): Soft-load for optional functions (may be NULL)
#define GPU__LOAD_DEVICE_FN_OPT(fn) do { \
    union { PFN_vkVoidFunction vk; __typeof__(dev->vk.fn) typed; } gpu__u; \
    gpu__u.vk = dev->vk.vkGetDeviceProcAddr(dev->device, #fn); \
    dev->vk.fn = gpu__u.typed; \
} while(0)

////////////////////////////////
//~ sa: Device Creation

GPU_API GPU_Device *
gpu_device_create(GPU_DeviceDesc *desc)
{
    GPU_Device *dev = (GPU_Device *)GPU_MALLOC(sizeof(GPU_Device));
    GPU_MemoryZeroStruct(dev);

    //- Load Vulkan library
#if defined(GPU_OS_WINDOWS)
    dev->vk_lib = (void *)LoadLibraryA("vulkan-1.dll");
    GPU_ASSERT(dev->vk_lib && "Failed to load vulkan-1.dll");
    PFN_vkGetInstanceProcAddr get_instance_proc =
        (PFN_vkGetInstanceProcAddr)(void *)GetProcAddress((HMODULE)dev->vk_lib, "vkGetInstanceProcAddr");
#else
    dev->vk_lib = dlopen("libvulkan.so.1", RTLD_NOW | RTLD_LOCAL);
    if (!dev->vk_lib) dev->vk_lib = dlopen("libvulkan.so", RTLD_NOW | RTLD_LOCAL);
    GPU_ASSERT(dev->vk_lib && "Failed to load libvulkan.so");
    PFN_vkGetInstanceProcAddr get_instance_proc =
        (PFN_vkGetInstanceProcAddr)dlsym(dev->vk_lib, "vkGetInstanceProcAddr");
#endif
    GPU_ASSERT(get_instance_proc);

    //- Pre-instance function loading
    VkResult (*vkCreateInstance)(const void*, const void*, VkInstance*) =
        (VkResult (*)(const void*, const void*, VkInstance*))get_instance_proc(0, "vkCreateInstance");
    GPU_ASSERT(vkCreateInstance);

    //- Create Instance (Vulkan 1.3 required)
    {
        struct {
            VkStructureType sType;
            const void *pNext;
            const char *pApplicationName;
            U32 applicationVersion;
            const char *pEngineName;
            U32 engineVersion;
            U32 apiVersion;
        } app_info = {
            .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
            .pApplicationName = desc->app_name ? desc->app_name : "gpu.h",
            .apiVersion = VK_API_VERSION_1_3,
        };

        const char *layers[1] = {0};
        U32 layer_count = 0;
        const char *extensions[4] = {0};
        U32 ext_count = 0;

        if (desc->enable_validation) {
            layers[layer_count++] = "VK_LAYER_KHRONOS_validation";
            dev->validation_enabled = 1;
        }

        if (desc->enable_surface) {
            extensions[ext_count++] = "VK_KHR_surface";
#if defined(GPU_OS_WINDOWS)
            extensions[ext_count++] = "VK_KHR_win32_surface";
#elif defined(GPU_OS_LINUX)
            extensions[ext_count++] = "VK_KHR_xcb_surface";
#endif
            dev->surface_enabled = 1;
        }

        struct {
            VkStructureType sType;
            const void *pNext;
            VkFlags flags;
            const void *pApplicationInfo;
            U32 enabledLayerCount;
            const char *const *ppEnabledLayerNames;
            U32 enabledExtensionCount;
            const char *const *ppEnabledExtensionNames;
        } instance_ci = {
            .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            .pApplicationInfo = &app_info,
            .enabledLayerCount = layer_count,
            .ppEnabledLayerNames = layers,
            .enabledExtensionCount = ext_count,
            .ppEnabledExtensionNames = extensions,
        };

        VkResult r = vkCreateInstance(&instance_ci, 0, &dev->instance);
        GPU_ASSERT(r == VK_SUCCESS && "Failed to create Vulkan instance");
    }

    //- Load instance-level functions
    GPU__LOAD_INSTANCE_FN(vkDestroyInstance);
    GPU__LOAD_INSTANCE_FN(vkEnumeratePhysicalDevices);
    GPU__LOAD_INSTANCE_FN(vkGetPhysicalDeviceProperties);
    GPU__LOAD_INSTANCE_FN(vkGetPhysicalDeviceMemoryProperties);
    GPU__LOAD_INSTANCE_FN(vkGetPhysicalDeviceQueueFamilyProperties);
    GPU__LOAD_INSTANCE_FN(vkCreateDevice);

    if (dev->surface_enabled) {
#if defined(GPU_OS_WINDOWS)
        GPU__LOAD_INSTANCE_FN(vkCreateWin32SurfaceKHR);
#elif defined(GPU_OS_LINUX)
        GPU__LOAD_INSTANCE_FN(vkCreateXcbSurfaceKHR);
#endif
        GPU__LOAD_INSTANCE_FN(vkDestroySurfaceKHR);
        GPU__LOAD_INSTANCE_FN(vkGetPhysicalDeviceSurfaceSupportKHR);
        GPU__LOAD_INSTANCE_FN(vkGetPhysicalDeviceSurfaceCapabilitiesKHR);
        GPU__LOAD_INSTANCE_FN(vkGetPhysicalDeviceSurfaceFormatsKHR);
        GPU__LOAD_INSTANCE_FN(vkGetPhysicalDeviceSurfacePresentModesKHR);
    }

    //- Pick physical device (first discrete GPU, or first available)
    {
        U32 count = 0;
        dev->vk.vkEnumeratePhysicalDevices(dev->instance, &count, 0);
        GPU_ASSERT(count > 0 && "No Vulkan physical devices found");

        VkPhysicalDevice devices[16];
        U32 actual = GPU_Min(count, 16);
        dev->vk.vkEnumeratePhysicalDevices(dev->instance, &actual, devices);

        // Prefer discrete GPU
        dev->physical_device = devices[0];
        for (U32 i = 0; i < actual; i += 1) {
            VkPhysicalDeviceProperties props;
            dev->vk.vkGetPhysicalDeviceProperties(devices[i], &props);
            if (props.deviceType == 2 /* VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU */) {
                dev->physical_device = devices[i];
                break;
            }
        }

        dev->vk.vkGetPhysicalDeviceMemoryProperties(dev->physical_device, &dev->mem_props);
    }

    //- Find queue families
    {
        U32 count = 0;
        dev->vk.vkGetPhysicalDeviceQueueFamilyProperties(dev->physical_device, &count, 0);
        VkQueueFamilyProperties families[32];
        U32 actual = GPU_Min(count, 32);
        dev->vk.vkGetPhysicalDeviceQueueFamilyProperties(dev->physical_device, &actual, families);

        #define VK_QUEUE_GRAPHICS_BIT 0x00000001
        #define VK_QUEUE_COMPUTE_BIT  0x00000002
        #define VK_QUEUE_TRANSFER_BIT 0x00000004

        dev->graphics_queue_family = 0;
        dev->compute_queue_family = 0;
        dev->transfer_queue_family = 0;

        for (U32 i = 0; i < actual; i += 1) {
            if (families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                dev->graphics_queue_family = i;
                break;
            }
        }
        dev->compute_queue_family = dev->graphics_queue_family;
        dev->transfer_queue_family = dev->graphics_queue_family;
    }

    //- Create logical device with required Vulkan 1.3 features
    {
        F32 priority = 1.0f;
        struct {
            VkStructureType sType;
            const void *pNext;
            VkFlags flags;
            U32 queueFamilyIndex;
            U32 queueCount;
            const F32 *pQueuePriorities;
        } queue_ci = {
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .queueFamilyIndex = dev->graphics_queue_family,
            .queueCount = 1,
            .pQueuePriorities = &priority,
        };

        // Enable Vulkan 1.3 features: dynamic rendering, synchronization2, timeline semaphores
        struct {
            VkStructureType sType;
            void *pNext;
            VkBool32 dynamicRendering;
        } dynamic_rendering_features = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES,
            .dynamicRendering = VK_TRUE,
        };

        struct {
            VkStructureType sType;
            void *pNext;
            VkBool32 synchronization2;
        } sync2_features = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SYNCHRONIZATION_2_FEATURES,
            .pNext = &dynamic_rendering_features,
            .synchronization2 = VK_TRUE,
        };

        // Buffer device address + timeline semaphore via Vulkan 1.2 features
        // NOTE(sa): VkPhysicalDeviceVulkan12Features has 47 VkBool32 fields.
        // We lay out the full struct to avoid offset guessing.
        struct {
            VkStructureType sType;
            void *pNext;
            VkBool32 samplerMirrorClampToEdge;           // 0
            VkBool32 drawIndirectCount;                   // 1
            VkBool32 storageBuffer8BitAccess;             // 2
            VkBool32 uniformAndStorageBuffer8BitAccess;   // 3
            VkBool32 storagePushConstant8;                // 4
            VkBool32 shaderBufferInt64Atomics;            // 5
            VkBool32 shaderSharedInt64Atomics;            // 6
            VkBool32 shaderFloat16;                       // 7
            VkBool32 shaderInt8;                          // 8
            VkBool32 descriptorIndexing;                  // 9
            VkBool32 shaderInputAttachmentArrayDynamicIndexing;          // 10
            VkBool32 shaderUniformTexelBufferArrayDynamicIndexing;       // 11
            VkBool32 shaderStorageTexelBufferArrayDynamicIndexing;       // 12
            VkBool32 shaderUniformBufferArrayNonUniformIndexing;         // 13
            VkBool32 shaderSampledImageArrayNonUniformIndexing;          // 14
            VkBool32 shaderStorageBufferArrayNonUniformIndexing;         // 15
            VkBool32 shaderStorageImageArrayNonUniformIndexing;          // 16
            VkBool32 shaderInputAttachmentArrayNonUniformIndexing;       // 17
            VkBool32 shaderUniformTexelBufferArrayNonUniformIndexing;    // 18
            VkBool32 shaderStorageTexelBufferArrayNonUniformIndexing;    // 19
            VkBool32 descriptorBindingUniformBufferUpdateAfterBind;      // 20
            VkBool32 descriptorBindingSampledImageUpdateAfterBind;       // 21
            VkBool32 descriptorBindingStorageImageUpdateAfterBind;       // 22
            VkBool32 descriptorBindingStorageBufferUpdateAfterBind;      // 23
            VkBool32 descriptorBindingUniformTexelBufferUpdateAfterBind; // 24
            VkBool32 descriptorBindingStorageTexelBufferUpdateAfterBind; // 25
            VkBool32 descriptorBindingUpdateUnusedWhilePending;          // 26
            VkBool32 descriptorBindingPartiallyBound;                    // 27
            VkBool32 descriptorBindingVariableDescriptorCount;           // 28
            VkBool32 runtimeDescriptorArray;                             // 29
            VkBool32 samplerFilterMinmax;                 // 30
            VkBool32 scalarBlockLayout;                   // 31
            VkBool32 imagelessFramebuffer;                // 32
            VkBool32 uniformBufferStandardLayout;         // 33
            VkBool32 shaderSubgroupExtendedTypes;         // 34
            VkBool32 separateDepthStencilLayouts;         // 35
            VkBool32 hostQueryReset;                      // 36
            VkBool32 timelineSemaphore;                   // 37
            VkBool32 bufferDeviceAddress;                 // 38
            VkBool32 bufferDeviceAddressCaptureReplay;    // 39
            VkBool32 bufferDeviceAddressMultiDevice;      // 40
            VkBool32 vulkanMemoryModel;                   // 41
            VkBool32 vulkanMemoryModelDeviceScope;        // 42
            VkBool32 vulkanMemoryModelAvailabilityVisibilityChains; // 43
            VkBool32 shaderOutputViewportIndex;           // 44
            VkBool32 shaderOutputLayer;                   // 45
            VkBool32 subgroupBroadcastDynamicId;          // 46
        } vk12_features;
        GPU_MemoryZeroStruct(&vk12_features);
        vk12_features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
        vk12_features.pNext = &sync2_features;
        vk12_features.timelineSemaphore = VK_TRUE;
        vk12_features.bufferDeviceAddress = VK_TRUE;
        vk12_features.scalarBlockLayout = VK_TRUE;
        vk12_features.drawIndirectCount = VK_TRUE;

        const char *dev_extensions[4] = {0};
        U32 dev_ext_count = 0;
        if (dev->surface_enabled) {
            dev_extensions[dev_ext_count++] = "VK_KHR_swapchain";
        }

        struct {
            VkStructureType sType;
            const void *pNext;
            VkFlags flags;
            U32 queueCreateInfoCount;
            const void *pQueueCreateInfos;
            U32 enabledLayerCount;
            const char *const *ppEnabledLayerNames;
            U32 enabledExtensionCount;
            const char *const *ppEnabledExtensionNames;
            const void *pEnabledFeatures;
        } device_ci = {
            .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
            .pNext = &vk12_features,
            .queueCreateInfoCount = 1,
            .pQueueCreateInfos = &queue_ci,
            .enabledExtensionCount = dev_ext_count,
            .ppEnabledExtensionNames = dev_extensions,
        };

        VkResult r = dev->vk.vkCreateDevice(dev->physical_device, &device_ci, 0, &dev->device);
        GPU_ASSERT(r == VK_SUCCESS && "Failed to create Vulkan logical device");
    }

    //- Load device-level functions
    dev->vk.vkGetDeviceProcAddr = (PFN_vkVoidFunction (*)(VkDevice, const char*))
        get_instance_proc(dev->instance, "vkGetDeviceProcAddr");

    GPU__LOAD_DEVICE_FN(vkDestroyDevice);
    GPU__LOAD_DEVICE_FN(vkGetDeviceQueue);
    GPU__LOAD_DEVICE_FN(vkDeviceWaitIdle);
    GPU__LOAD_DEVICE_FN(vkQueueWaitIdle);
    GPU__LOAD_DEVICE_FN(vkAllocateMemory);
    GPU__LOAD_DEVICE_FN(vkFreeMemory);
    GPU__LOAD_DEVICE_FN(vkMapMemory);
    GPU__LOAD_DEVICE_FN(vkUnmapMemory);
    GPU__LOAD_DEVICE_FN(vkGetBufferMemoryRequirements);
    GPU__LOAD_DEVICE_FN(vkGetImageMemoryRequirements);
    GPU__LOAD_DEVICE_FN(vkBindBufferMemory);
    GPU__LOAD_DEVICE_FN(vkBindImageMemory);
    GPU__LOAD_DEVICE_FN(vkCreateBuffer);
    GPU__LOAD_DEVICE_FN(vkDestroyBuffer);
    GPU__LOAD_DEVICE_FN(vkGetBufferDeviceAddress);
    GPU__LOAD_DEVICE_FN(vkCreateImage);
    GPU__LOAD_DEVICE_FN(vkDestroyImage);
    GPU__LOAD_DEVICE_FN(vkCreateImageView);
    GPU__LOAD_DEVICE_FN(vkDestroyImageView);
    GPU__LOAD_DEVICE_FN(vkCreateShaderModule);
    GPU__LOAD_DEVICE_FN(vkDestroyShaderModule);
    GPU__LOAD_DEVICE_FN(vkCreatePipelineLayout);
    GPU__LOAD_DEVICE_FN(vkDestroyPipelineLayout);
    GPU__LOAD_DEVICE_FN(vkCreateGraphicsPipelines);
    GPU__LOAD_DEVICE_FN(vkCreateComputePipelines);
    GPU__LOAD_DEVICE_FN(vkDestroyPipeline);
    GPU__LOAD_DEVICE_FN(vkCreateCommandPool);
    GPU__LOAD_DEVICE_FN(vkDestroyCommandPool);
    GPU__LOAD_DEVICE_FN(vkAllocateCommandBuffers);
    GPU__LOAD_DEVICE_FN(vkFreeCommandBuffers);
    GPU__LOAD_DEVICE_FN(vkBeginCommandBuffer);
    GPU__LOAD_DEVICE_FN(vkEndCommandBuffer);
    GPU__LOAD_DEVICE_FN(vkResetCommandPool);
    GPU__LOAD_DEVICE_FN(vkCmdBindPipeline);
    GPU__LOAD_DEVICE_FN(vkCmdPushConstants);
    GPU__LOAD_DEVICE_FN(vkCmdSetViewport);
    GPU__LOAD_DEVICE_FN(vkCmdSetScissor);
    GPU__LOAD_DEVICE_FN(vkCmdDraw);
    GPU__LOAD_DEVICE_FN(vkCmdDrawIndexed);
    GPU__LOAD_DEVICE_FN(vkCmdDrawIndirect);
    GPU__LOAD_DEVICE_FN(vkCmdDrawIndexedIndirect);
    GPU__LOAD_DEVICE_FN(vkCmdDispatch);
    GPU__LOAD_DEVICE_FN(vkCmdDispatchIndirect);
    GPU__LOAD_DEVICE_FN(vkCmdBindIndexBuffer);
    GPU__LOAD_DEVICE_FN(vkCmdCopyBuffer);
    GPU__LOAD_DEVICE_FN(vkCmdCopyBufferToImage);
    GPU__LOAD_DEVICE_FN(vkCmdCopyImageToBuffer);
    GPU__LOAD_DEVICE_FN(vkCmdBeginRendering);
    GPU__LOAD_DEVICE_FN(vkCmdEndRendering);
    GPU__LOAD_DEVICE_FN(vkCmdPipelineBarrier2);
    GPU__LOAD_DEVICE_FN(vkQueueSubmit2);
    GPU__LOAD_DEVICE_FN(vkCreateSemaphore);
    GPU__LOAD_DEVICE_FN(vkDestroySemaphore);
    GPU__LOAD_DEVICE_FN(vkWaitSemaphores);
    GPU__LOAD_DEVICE_FN(vkGetSemaphoreCounterValue);
    GPU__LOAD_DEVICE_FN(vkCreateFence);
    GPU__LOAD_DEVICE_FN(vkDestroyFence);
    GPU__LOAD_DEVICE_FN(vkWaitForFences);
    GPU__LOAD_DEVICE_FN(vkResetFences);
    GPU__LOAD_DEVICE_FN(vkCmdSetDepthTestEnable);
    GPU__LOAD_DEVICE_FN(vkCmdSetDepthWriteEnable);
    GPU__LOAD_DEVICE_FN(vkCmdSetDepthCompareOp);

    GPU__LOAD_DEVICE_FN_OPT(vkCmdDrawIndexedIndirectCount);
    GPU__LOAD_DEVICE_FN_OPT(vkSignalSemaphore);

    if (dev->surface_enabled) {
        GPU__LOAD_DEVICE_FN(vkCreateSwapchainKHR);
        GPU__LOAD_DEVICE_FN(vkDestroySwapchainKHR);
        GPU__LOAD_DEVICE_FN(vkGetSwapchainImagesKHR);
        GPU__LOAD_DEVICE_FN(vkAcquireNextImageKHR);
        GPU__LOAD_DEVICE_FN(vkQueuePresentKHR);
    }

    //- Create shared pipeline layout with 2x U64 push constants
    // This supports the "single root pointer" model: vertex_data_gpu + pixel_data_gpu
    {
        struct {
            VkStructureType sType;
            const void *pNext;
            VkFlags flags;
            U32 setLayoutCount;
            const VkDescriptorSetLayout *pSetLayouts;
            U32 pushConstantRangeCount;
            const void *pPushConstantRanges;
        } layout_ci;
        GPU_MemoryZeroStruct(&layout_ci);
        layout_ci.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

        struct {
            VkFlags stageFlags;
            U32 offset;
            U32 size;
        } push_range = {
            .stageFlags = VK_SHADER_STAGE_ALL,
            .offset = 0,
            .size = 2 * sizeof(U64), // vertex_data_gpu + pixel_data_gpu
        };
        layout_ci.pushConstantRangeCount = 1;
        layout_ci.pPushConstantRanges = &push_range;

        VkResult r = dev->vk.vkCreatePipelineLayout(dev->device, &layout_ci, 0, &dev->push_constant_layout);
        GPU_ASSERT(r == VK_SUCCESS);
    }

    return dev;
}

GPU_API void
gpu_device_destroy(GPU_Device *dev)
{
    dev->vk.vkDeviceWaitIdle(dev->device);
    dev->vk.vkDestroyPipelineLayout(dev->device, dev->push_constant_layout, 0);
    dev->vk.vkDestroyDevice(dev->device, 0);
    dev->vk.vkDestroyInstance(dev->instance, 0);
#if defined(GPU_OS_WINDOWS)
    if (dev->vk_lib) FreeLibrary((HMODULE)dev->vk_lib);
#else
    if (dev->vk_lib) dlclose(dev->vk_lib);
#endif
    GPU_FREE(dev);
}

////////////////////////////////
//~ sa: Memory Allocation (gpuMalloc / gpuFree)

GPU_API GPU_Alloc *
gpu_malloc_aligned(GPU_Device *dev, U64 size, U64 align, GPU_MemoryKind kind)
{
    GPU_Alloc *alloc = (GPU_Alloc *)GPU_MALLOC(sizeof(GPU_Alloc));
    GPU_MemoryZeroStruct(alloc);
    alloc->kind = kind;
    alloc->size = size;

    //- Create buffer with all usage bits + shader device address
    VkFlags usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT |
                    VK_BUFFER_USAGE_TRANSFER_DST_BIT |
                    VK_BUFFER_USAGE_STORAGE_BUFFER_BIT |
                    VK_BUFFER_USAGE_INDEX_BUFFER_BIT |
                    VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT |
                    VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT;

    struct {
        VkStructureType sType;
        const void *pNext;
        VkFlags flags;
        VkDeviceSize size;
        VkFlags usage;
        S32 sharingMode;
        U32 queueFamilyIndexCount;
        const U32 *pQueueFamilyIndices;
    } buffer_ci = {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = size,
        .usage = usage,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
    };

    // Opaque capture address for buffer device address
    struct {
        VkStructureType sType;
        const void *pNext;
        U64 opaqueCaptureAddress;
    } opaque_addr = {
        .sType = VK_STRUCTURE_TYPE_BUFFER_OPAQUE_CAPTURE_ADDRESS_CREATE_INFO,
    };
    buffer_ci.pNext = &opaque_addr;

    VkResult r = dev->vk.vkCreateBuffer(dev->device, &buffer_ci, 0, &alloc->buffer);
    GPU_ASSERT(r == VK_SUCCESS);

    //- Query memory requirements
    VkMemoryRequirements mem_reqs;
    dev->vk.vkGetBufferMemoryRequirements(dev->device, alloc->buffer, &mem_reqs);

    //- Find memory type based on kind
    VkFlags mem_props = 0;
    switch (kind) {
        case GPU_MemoryKind_Default:
            mem_props = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT |
                        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
            break;
        case GPU_MemoryKind_GpuOnly:
            mem_props = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
            break;
        case GPU_MemoryKind_Readback:
            mem_props = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT;
            break;
        default: break;
    }

    S32 mem_type_idx = gpu__find_memory_type(dev, mem_reqs.memoryTypeBits, mem_props);

    // Fallback: if DEFAULT with DEVICE_LOCAL fails (no ReBAR), try without DEVICE_LOCAL
    if (mem_type_idx < 0 && kind == GPU_MemoryKind_Default) {
        mem_props = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
        mem_type_idx = gpu__find_memory_type(dev, mem_reqs.memoryTypeBits, mem_props);
    }

    // Fallback: readback without HOST_CACHED
    if (mem_type_idx < 0 && kind == GPU_MemoryKind_Readback) {
        mem_props = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
        mem_type_idx = gpu__find_memory_type(dev, mem_reqs.memoryTypeBits, mem_props);
    }

    GPU_ASSERT(mem_type_idx >= 0 && "No suitable memory type found");

    //- Allocate memory with device address flag
    struct {
        VkStructureType sType;
        const void *pNext;
        VkDeviceSize allocationSize;
        U32 memoryTypeIndex;
    } alloc_info = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .allocationSize = mem_reqs.size,
        .memoryTypeIndex = (U32)mem_type_idx,
    };

    struct {
        VkStructureType sType;
        const void *pNext;
        VkFlags flags;
    } flags_info = {
        .sType = 0x3B9D3B59, // VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO = 1000060000
        .flags = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT,
    };
    alloc_info.pNext = &flags_info;

    r = dev->vk.vkAllocateMemory(dev->device, &alloc_info, 0, &alloc->memory);
    GPU_ASSERT(r == VK_SUCCESS);

    r = dev->vk.vkBindBufferMemory(dev->device, alloc->buffer, alloc->memory, 0);
    GPU_ASSERT(r == VK_SUCCESS);

    //- Map memory for host-visible types
    if (kind != GPU_MemoryKind_GpuOnly) {
        r = dev->vk.vkMapMemory(dev->device, alloc->memory, 0, VK_WHOLE_SIZE, 0, &alloc->cpu_ptr);
        GPU_ASSERT(r == VK_SUCCESS);
    }

    //- Get buffer device address (64-bit GPU virtual address)
    {
        struct {
            VkStructureType sType;
            const void *pNext;
            VkBuffer buffer;
        } addr_info = {
            .sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO,
            .buffer = alloc->buffer,
        };
        alloc->device_addr = dev->vk.vkGetBufferDeviceAddress(dev->device, &addr_info);
    }

    return alloc;
}

GPU_API GPU_Alloc *
gpu_malloc(GPU_Device *dev, U64 size, GPU_MemoryKind kind)
{
    return gpu_malloc_aligned(dev, size, 16, kind);
}

GPU_API void
gpu_free(GPU_Device *dev, GPU_Alloc *alloc)
{
    if (!alloc) return;
    if (alloc->cpu_ptr && alloc->kind != GPU_MemoryKind_GpuOnly) {
        dev->vk.vkUnmapMemory(dev->device, alloc->memory);
    }
    dev->vk.vkDestroyBuffer(dev->device, alloc->buffer, 0);
    dev->vk.vkFreeMemory(dev->device, alloc->memory, 0);
    GPU_FREE(alloc);
}

GPU_API void *
gpu_alloc_cpu_ptr(GPU_Alloc *alloc) { return alloc->cpu_ptr; }

GPU_API U64
gpu_alloc_device_addr(GPU_Alloc *alloc) { return alloc->device_addr; }

GPU_API U64
gpu_alloc_size(GPU_Alloc *alloc) { return alloc->size; }

////////////////////////////////
//~ sa: Host-to-Device Pointer Mapping

GPU_API U64
gpu_host_to_device_ptr(GPU_Device *dev, GPU_Alloc *alloc, void *cpu_ptr)
{
    (void)dev;
    GPU_ASSERT(alloc->cpu_ptr && "Cannot map host pointer for GPU_ONLY memory");
    U64 offset = (U64)((U8 *)cpu_ptr - (U8 *)alloc->cpu_ptr);
    GPU_ASSERT(offset < alloc->size);
    return alloc->device_addr + offset;
}

////////////////////////////////
//~ sa: Textures

GPU_API GPU_TextureSizeAlign
gpu_texture_size_align(GPU_Device *dev, GPU_TextureDesc *desc)
{
    VkImage tmp_image;
    struct {
        VkStructureType sType;
        const void *pNext;
        VkFlags flags;
        S32 imageType;
        S32 format;
        VkExtent3D extent;
        U32 mipLevels;
        U32 arrayLayers;
        VkFlags samples;
        S32 tiling;
        VkFlags usage;
        S32 sharingMode;
        U32 queueFamilyIndexCount;
        const U32 *pQueueFamilyIndices;
        S32 initialLayout;
    } image_ci = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .imageType = VK_IMAGE_TYPE_2D,
        .format = gpu__vk_format(desc->format),
        .extent = { desc->width, desc->height, GPU_Max(desc->depth, 1) },
        .mipLevels = GPU_Max(desc->mip_levels, 1),
        .arrayLayers = 1,
        .samples = VK_SAMPLE_COUNT_1_BIT,
        .tiling = VK_IMAGE_TILING_OPTIMAL,
        .usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
    };

    if (desc->is_render_target) image_ci.usage |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    if (desc->is_depth_stencil) image_ci.usage |= VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    if (desc->is_storage)       image_ci.usage |= VK_IMAGE_USAGE_STORAGE_BIT;

    VkResult r = dev->vk.vkCreateImage(dev->device, &image_ci, 0, &tmp_image);
    GPU_ASSERT(r == VK_SUCCESS);

    VkMemoryRequirements mem_reqs;
    dev->vk.vkGetImageMemoryRequirements(dev->device, tmp_image, &mem_reqs);
    dev->vk.vkDestroyImage(dev->device, tmp_image, 0);

    GPU_TextureSizeAlign result = { .size = mem_reqs.size, .align = mem_reqs.alignment };
    return result;
}

GPU_API GPU_Texture *
gpu_texture_create(GPU_Device *dev, GPU_TextureDesc *desc, GPU_Alloc *memory)
{
    GPU_Texture *tex = (GPU_Texture *)GPU_MALLOC(sizeof(GPU_Texture));
    GPU_MemoryZeroStruct(tex);
    tex->desc = *desc;

    S32 vk_format = gpu__vk_format(desc->format);
    B32 is_depth = gpu__format_is_depth(desc->format);
    U32 mips = GPU_Max(desc->mip_levels, 1);

    //- Create image
    struct {
        VkStructureType sType;
        const void *pNext;
        VkFlags flags;
        S32 imageType;
        S32 format;
        VkExtent3D extent;
        U32 mipLevels;
        U32 arrayLayers;
        VkFlags samples;
        S32 tiling;
        VkFlags usage;
        S32 sharingMode;
        U32 queueFamilyIndexCount;
        const U32 *pQueueFamilyIndices;
        S32 initialLayout;
    } image_ci = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .imageType = VK_IMAGE_TYPE_2D,
        .format = vk_format,
        .extent = { desc->width, desc->height, GPU_Max(desc->depth, 1) },
        .mipLevels = mips,
        .arrayLayers = 1,
        .samples = VK_SAMPLE_COUNT_1_BIT,
        .tiling = VK_IMAGE_TILING_OPTIMAL,
        .usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
    };

    if (desc->is_render_target) image_ci.usage |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    if (desc->is_depth_stencil) image_ci.usage |= VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    if (desc->is_storage)       image_ci.usage |= VK_IMAGE_USAGE_STORAGE_BIT;

    VkResult r = dev->vk.vkCreateImage(dev->device, &image_ci, 0, &tex->image);
    GPU_ASSERT(r == VK_SUCCESS);

    //- Allocate and bind memory
    if (memory) {
        // Bind to user-provided allocation's device memory
        r = dev->vk.vkBindImageMemory(dev->device, tex->image, memory->memory, 0);
        GPU_ASSERT(r == VK_SUCCESS);
        tex->owns_memory = 0;
    } else {
        // Self-allocate
        VkMemoryRequirements mem_reqs;
        dev->vk.vkGetImageMemoryRequirements(dev->device, tex->image, &mem_reqs);

        S32 mem_type = gpu__find_memory_type(dev, mem_reqs.memoryTypeBits,
                                              VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        GPU_ASSERT(mem_type >= 0);

        struct {
            VkStructureType sType;
            const void *pNext;
            VkDeviceSize allocationSize;
            U32 memoryTypeIndex;
        } alloc_info = {
            .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
            .allocationSize = mem_reqs.size,
            .memoryTypeIndex = (U32)mem_type,
        };

        r = dev->vk.vkAllocateMemory(dev->device, &alloc_info, 0, &tex->memory);
        GPU_ASSERT(r == VK_SUCCESS);
        r = dev->vk.vkBindImageMemory(dev->device, tex->image, tex->memory, 0);
        GPU_ASSERT(r == VK_SUCCESS);
        tex->owns_memory = 1;
    }

    //- Create image view
    VkFlags aspect = is_depth ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT;

    struct {
        VkStructureType sType;
        const void *pNext;
        VkFlags flags;
        VkImage image;
        S32 viewType;
        S32 format;
        VkComponentMapping components;
        VkImageSubresourceRange subresourceRange;
    } view_ci = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .image = tex->image,
        .viewType = VK_IMAGE_VIEW_TYPE_2D,
        .format = vk_format,
        .components = { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY,
                        VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY },
        .subresourceRange = { aspect, 0, mips, 0, 1 },
    };

    r = dev->vk.vkCreateImageView(dev->device, &view_ci, 0, &tex->image_view);
    GPU_ASSERT(r == VK_SUCCESS);

    return tex;
}

GPU_API void
gpu_texture_destroy(GPU_Device *dev, GPU_Texture *tex)
{
    if (!tex) return;
    dev->vk.vkDestroyImageView(dev->device, tex->image_view, 0);
    dev->vk.vkDestroyImage(dev->device, tex->image, 0);
    if (tex->owns_memory) {
        dev->vk.vkFreeMemory(dev->device, tex->memory, 0);
    }
    GPU_FREE(tex);
}

GPU_API GPU_DescriptorBlob
gpu_texture_descriptor_blob(GPU_Device *dev, GPU_Texture *tex)
{
    // NOTE(sa): In a real "No Graphics API" implementation, this would return
    // the raw 256-bit hardware descriptor blob. In our Vulkan abstraction,
    // we store enough info to reconstruct the descriptor.
    (void)dev;
    GPU_DescriptorBlob blob = {0};
    blob.data[0] = tex->image_view;     // VkImageView handle
    blob.data[1] = (U64)gpu__vk_format(tex->desc.format);
    blob.data[2] = (U64)tex->desc.width | ((U64)tex->desc.height << 32);
    blob.data[3] = (U64)tex->desc.mip_levels;
    return blob;
}

////////////////////////////////
//~ sa: Dynamic State Objects

GPU_API GPU_BlendState *
gpu_blend_state_create(GPU_Device *dev, GPU_BlendDesc *desc)
{
    (void)dev;
    GPU_BlendState *state = (GPU_BlendState *)GPU_MALLOC(sizeof(GPU_BlendState));
    state->desc = *desc;
    return state;
}

GPU_API void
gpu_blend_state_destroy(GPU_Device *dev, GPU_BlendState *state)
{
    (void)dev;
    if (state) GPU_FREE(state);
}

GPU_API GPU_DepthStencilState *
gpu_depth_stencil_state_create(GPU_Device *dev, U32 depth_flags)
{
    (void)dev;
    GPU_DepthStencilState *state = (GPU_DepthStencilState *)GPU_MALLOC(sizeof(GPU_DepthStencilState));
    state->depth_test_enable = (depth_flags & GPU_DepthFlags_Read) ? 1 : 0;
    state->depth_write_enable = (depth_flags & GPU_DepthFlags_Write) ? 1 : 0;
    state->compare_op = VK_COMPARE_OP_LESS;
    return state;
}

GPU_API void
gpu_depth_stencil_state_destroy(GPU_Device *dev, GPU_DepthStencilState *state)
{
    (void)dev;
    if (state) GPU_FREE(state);
}

////////////////////////////////
//~ sa: Pipelines (Shader Objects)

internal VkShaderModule
gpu__create_shader_module(GPU_Device *dev, const U8 *spirv, U64 spirv_size)
{
    struct {
        VkStructureType sType;
        const void *pNext;
        VkFlags flags;
        U64 codeSize;
        const U32 *pCode;
    } ci = {
        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .codeSize = spirv_size,
        .pCode = (const U32 *)spirv,
    };
    VkShaderModule module = VK_NULL_HANDLE;
    VkResult r = dev->vk.vkCreateShaderModule(dev->device, &ci, 0, &module);
    GPU_ASSERT(r == VK_SUCCESS);
    return module;
}

GPU_API GPU_Pipeline *
gpu_pipeline_compute_create(GPU_Device *dev, const U8 *spirv, U64 spirv_size)
{
    GPU_Pipeline *pip = (GPU_Pipeline *)GPU_MALLOC(sizeof(GPU_Pipeline));
    GPU_MemoryZeroStruct(pip);
    pip->bind_point = VK_PIPELINE_BIND_POINT_COMPUTE;
    pip->layout = dev->push_constant_layout;

    VkShaderModule module = gpu__create_shader_module(dev, spirv, spirv_size);

    // Compute pipeline create info (laid out manually)
    struct {
        VkStructureType sType;
        const void *pNext;
        VkFlags flags;
        struct {
            VkStructureType sType;
            const void *pNext;
            VkFlags flags;
            S32 stage;
            VkShaderModule module;
            const char *pName;
            const void *pSpecializationInfo;
        } stage;
        VkPipelineLayout layout;
        VkPipeline_Vk basePipelineHandle;
        S32 basePipelineIndex;
    } comp_ci = {
        .sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
        .stage = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .stage = VK_SHADER_STAGE_COMPUTE_BIT,
            .module = module,
            .pName = "main",
        },
        .layout = pip->layout,
        .basePipelineIndex = -1,
    };

    VkResult r = dev->vk.vkCreateComputePipelines(dev->device, VK_NULL_HANDLE, 1, &comp_ci, 0, &pip->pipeline);
    GPU_ASSERT(r == VK_SUCCESS);

    dev->vk.vkDestroyShaderModule(dev->device, module, 0);
    return pip;
}

GPU_API GPU_Pipeline *
gpu_pipeline_graphics_create(GPU_Device *dev,
                              const U8 *vert_spirv, U64 vert_spirv_size,
                              const U8 *frag_spirv, U64 frag_spirv_size,
                              GPU_RasterDesc *raster_desc)
{
    GPU_Pipeline *pip = (GPU_Pipeline *)GPU_MALLOC(sizeof(GPU_Pipeline));
    GPU_MemoryZeroStruct(pip);
    pip->bind_point = VK_PIPELINE_BIND_POINT_GRAPHICS;
    pip->layout = dev->push_constant_layout;

    VkShaderModule vert_mod = gpu__create_shader_module(dev, vert_spirv, vert_spirv_size);
    VkShaderModule frag_mod = gpu__create_shader_module(dev, frag_spirv, frag_spirv_size);

    //- Shader stages
    struct {
        VkStructureType sType;
        const void *pNext;
        VkFlags flags;
        S32 stage;
        VkShaderModule module;
        const char *pName;
        const void *pSpecializationInfo;
    } stages[2] = {
        {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .stage = VK_SHADER_STAGE_VERTEX_BIT,
            .module = vert_mod,
            .pName = "main",
        },
        {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
            .module = frag_mod,
            .pName = "main",
        },
    };

    //- Vertex input: EMPTY (manual vertex pulling via 64-bit pointers)
    struct {
        VkStructureType sType;
        const void *pNext;
        VkFlags flags;
        U32 vertexBindingDescriptionCount;
        const void *pVertexBindingDescriptions;
        U32 vertexAttributeDescriptionCount;
        const void *pVertexAttributeDescriptions;
    } vertex_input = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
    };

    //- Input assembly
    struct {
        VkStructureType sType;
        const void *pNext;
        VkFlags flags;
        S32 topology;
        VkBool32 primitiveRestartEnable;
    } input_assembly = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
    };

    //- Viewport/scissor (dynamic)
    struct {
        VkStructureType sType;
        const void *pNext;
        VkFlags flags;
        U32 viewportCount;
        const void *pViewports;
        U32 scissorCount;
        const void *pScissors;
    } viewport_state = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        .viewportCount = 1,
        .scissorCount = 1,
    };

    //- Rasterization
    S32 cull_mode = VK_CULL_MODE_NONE;
    S32 front_face = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    if (raster_desc) {
        switch (raster_desc->cull_mode) {
            case GPU_CullMode_FrontCCW: cull_mode = VK_CULL_MODE_BACK_BIT; front_face = VK_FRONT_FACE_COUNTER_CLOCKWISE; break;
            case GPU_CullMode_FrontCW:  cull_mode = VK_CULL_MODE_BACK_BIT; front_face = VK_FRONT_FACE_CLOCKWISE; break;
            case GPU_CullMode_All:      cull_mode = VK_CULL_MODE_FRONT_BIT | VK_CULL_MODE_BACK_BIT; break;
            default: break;
        }
    }

    struct {
        VkStructureType sType;
        const void *pNext;
        VkFlags flags;
        VkBool32 depthClampEnable;
        VkBool32 rasterizerDiscardEnable;
        S32 polygonMode;
        VkFlags cullMode;
        S32 frontFace;
        VkBool32 depthBiasEnable;
        F32 depthBiasConstantFactor;
        F32 depthBiasClamp;
        F32 depthBiasSlopeFactor;
        F32 lineWidth;
    } rasterization = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .polygonMode = (raster_desc && raster_desc->wireframe) ? VK_POLYGON_MODE_LINE : VK_POLYGON_MODE_FILL,
        .cullMode = (VkFlags)cull_mode,
        .frontFace = front_face,
        .lineWidth = 1.0f,
    };

    //- Multisample
    struct {
        VkStructureType sType;
        const void *pNext;
        VkFlags flags;
        VkFlags rasterizationSamples;
        VkBool32 sampleShadingEnable;
        F32 minSampleShading;
        const void *pSampleMask;
        VkBool32 alphaToCoverageEnable;
        VkBool32 alphaToOneEnable;
    } multisample = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
    };

    //- Depth stencil (dynamic in Vulkan 1.3, but needed for pipeline creation)
    struct {
        VkStructureType sType;
        const void *pNext;
        VkFlags flags;
        VkBool32 depthTestEnable;
        VkBool32 depthWriteEnable;
        S32 depthCompareOp;
        VkBool32 depthBoundsTestEnable;
        VkBool32 stencilTestEnable;
        U8 front[28]; // VkStencilOpState
        U8 back[28];
        F32 minDepthBounds;
        F32 maxDepthBounds;
    } depth_stencil = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
        .depthTestEnable = VK_TRUE,
        .depthWriteEnable = VK_TRUE,
        .depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL,
    };

    //- Color blend (default: no blending)
    struct {
        VkBool32 blendEnable;
        S32 srcColorBlendFactor;
        S32 dstColorBlendFactor;
        S32 colorBlendOp;
        S32 srcAlphaBlendFactor;
        S32 dstAlphaBlendFactor;
        S32 alphaBlendOp;
        VkFlags colorWriteMask;
    } blend_attachment = {
        .blendEnable = VK_FALSE,
        .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                          VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
    };

    struct {
        VkStructureType sType;
        const void *pNext;
        VkFlags flags;
        VkBool32 logicOpEnable;
        S32 logicOp;
        U32 attachmentCount;
        const void *pAttachments;
        F32 blendConstants[4];
    } color_blend = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        .attachmentCount = 1,
        .pAttachments = &blend_attachment,
    };

    //- Dynamic state
    S32 dynamic_states[] = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR,
    };

    struct {
        VkStructureType sType;
        const void *pNext;
        VkFlags flags;
        U32 dynamicStateCount;
        const S32 *pDynamicStates;
    } dynamic_state = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        .dynamicStateCount = GPU_ArrayCount(dynamic_states),
        .pDynamicStates = dynamic_states,
    };

    //- Rendering info for dynamic rendering (no render pass)
    S32 color_format = (raster_desc && raster_desc->color_format) ?
                        gpu__vk_format(raster_desc->color_format) : VK_FORMAT_R8G8B8A8_UNORM;
    S32 depth_format = (raster_desc && raster_desc->depth_format) ?
                        gpu__vk_format(raster_desc->depth_format) : VK_FORMAT_D32_SFLOAT;
    struct {
        VkStructureType sType;
        const void *pNext;
        U32 viewMask;
        U32 colorAttachmentCount;
        const S32 *pColorAttachmentFormats;
        S32 depthAttachmentFormat;
        S32 stencilAttachmentFormat;
    } rendering_ci = {
        .sType = 1000044002, // VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO
        .colorAttachmentCount = 1,
        .pColorAttachmentFormats = &color_format,
        .depthAttachmentFormat = depth_format,
    };

    //- Graphics pipeline create info
    struct {
        VkStructureType sType;
        const void *pNext;
        VkFlags flags;
        U32 stageCount;
        const void *pStages;
        const void *pVertexInputState;
        const void *pInputAssemblyState;
        const void *pTessellationState;
        const void *pViewportState;
        const void *pRasterizationState;
        const void *pMultisampleState;
        const void *pDepthStencilState;
        const void *pColorBlendState;
        const void *pDynamicState;
        VkPipelineLayout layout;
        VkRenderPass renderPass;
        U32 subpass;
        VkPipeline_Vk basePipelineHandle;
        S32 basePipelineIndex;
    } gfx_ci = {
        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .pNext = &rendering_ci,
        .stageCount = 2,
        .pStages = stages,
        .pVertexInputState = &vertex_input,
        .pInputAssemblyState = &input_assembly,
        .pViewportState = &viewport_state,
        .pRasterizationState = &rasterization,
        .pMultisampleState = &multisample,
        .pDepthStencilState = &depth_stencil,
        .pColorBlendState = &color_blend,
        .pDynamicState = &dynamic_state,
        .layout = pip->layout,
        .basePipelineIndex = -1,
    };

    VkResult r = dev->vk.vkCreateGraphicsPipelines(dev->device, VK_NULL_HANDLE, 1, &gfx_ci, 0, &pip->pipeline);
    GPU_ASSERT(r == VK_SUCCESS);

    dev->vk.vkDestroyShaderModule(dev->device, vert_mod, 0);
    dev->vk.vkDestroyShaderModule(dev->device, frag_mod, 0);

    return pip;
}

GPU_API void
gpu_pipeline_destroy(GPU_Device *dev, GPU_Pipeline *pip)
{
    if (!pip) return;
    dev->vk.vkDestroyPipeline(dev->device, pip->pipeline, 0);
    GPU_FREE(pip);
}

////////////////////////////////
//~ sa: Queues

GPU_API GPU_Queue *
gpu_queue_create(GPU_Device *dev)
{
    GPU_Queue *q = (GPU_Queue *)GPU_MALLOC(sizeof(GPU_Queue));
    GPU_MemoryZeroStruct(q);

    q->family_index = dev->graphics_queue_family;
    dev->vk.vkGetDeviceQueue(dev->device, q->family_index, 0, &q->vk_queue);

    struct {
        VkStructureType sType;
        const void *pNext;
        VkFlags flags;
        U32 queueFamilyIndex;
    } pool_ci = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
        .queueFamilyIndex = q->family_index,
    };

    VkResult r = dev->vk.vkCreateCommandPool(dev->device, &pool_ci, 0, &q->cmd_pool);
    GPU_ASSERT(r == VK_SUCCESS);

    return q;
}

GPU_API void
gpu_queue_destroy(GPU_Device *dev, GPU_Queue *q)
{
    if (!q) return;
    dev->vk.vkDestroyCommandPool(dev->device, q->cmd_pool, 0);
    GPU_FREE(q);
}

////////////////////////////////
//~ sa: Semaphores (Timeline)

GPU_API GPU_Semaphore *
gpu_semaphore_create(GPU_Device *dev, U64 initial_value)
{
    GPU_Semaphore *sem = (GPU_Semaphore *)GPU_MALLOC(sizeof(GPU_Semaphore));
    GPU_MemoryZeroStruct(sem);

    struct {
        VkStructureType sType;
        const void *pNext;
        S32 semaphoreType;
        U64 initialValue;
    } type_ci = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
        .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
        .initialValue = initial_value,
    };

    struct {
        VkStructureType sType;
        const void *pNext;
        VkFlags flags;
    } sem_ci = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        .pNext = &type_ci,
    };

    VkResult r = dev->vk.vkCreateSemaphore(dev->device, &sem_ci, 0, &sem->vk_sem);
    GPU_ASSERT(r == VK_SUCCESS);

    return sem;
}

GPU_API void
gpu_semaphore_destroy(GPU_Device *dev, GPU_Semaphore *sem)
{
    if (!sem) return;
    dev->vk.vkDestroySemaphore(dev->device, sem->vk_sem, 0);
    GPU_FREE(sem);
}

GPU_API void
gpu_semaphore_wait(GPU_Device *dev, GPU_Semaphore *sem, U64 value)
{
    struct {
        VkStructureType sType;
        const void *pNext;
        VkFlags flags;
        U32 semaphoreCount;
        const VkSemaphore *pSemaphores;
        const U64 *pValues;
    } wait_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .semaphoreCount = 1,
        .pSemaphores = &sem->vk_sem,
        .pValues = &value,
    };

    VkResult r = dev->vk.vkWaitSemaphores(dev->device, &wait_info, ~(U64)0);
    GPU_ASSERT(r == VK_SUCCESS || r == VK_TIMEOUT);
}

GPU_API U64
gpu_semaphore_query(GPU_Device *dev, GPU_Semaphore *sem)
{
    U64 value = 0;
    dev->vk.vkGetSemaphoreCounterValue(dev->device, sem->vk_sem, &value);
    return value;
}

////////////////////////////////
//~ sa: Command Buffer Recording

GPU_API GPU_CmdBuf *
gpu_cmd_begin(GPU_Device *dev, GPU_Queue *queue)
{
    GPU_CmdBuf *cb = (GPU_CmdBuf *)GPU_MALLOC(sizeof(GPU_CmdBuf));
    GPU_MemoryZeroStruct(cb);
    cb->queue = queue;
    cb->device = dev;
    cb->bound_layout = dev->push_constant_layout;

    struct {
        VkStructureType sType;
        const void *pNext;
        VkCommandPool commandPool;
        S32 level;
        U32 commandBufferCount;
    } alloc_info = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .commandPool = queue->cmd_pool,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = 1,
    };

    VkResult r = dev->vk.vkAllocateCommandBuffers(dev->device, &alloc_info, &cb->vk_cb);
    GPU_ASSERT(r == VK_SUCCESS);

    struct {
        VkStructureType sType;
        const void *pNext;
        VkFlags flags;
        const void *pInheritanceInfo;
    } begin_info = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
    };

    r = dev->vk.vkBeginCommandBuffer(cb->vk_cb, &begin_info);
    GPU_ASSERT(r == VK_SUCCESS);

    return cb;
}

GPU_API void
gpu_cmd_set_pipeline(GPU_CmdBuf *cb, GPU_Pipeline *pip)
{
    cb->device->vk.vkCmdBindPipeline(cb->vk_cb, pip->bind_point, pip->pipeline);
    cb->bound_layout = pip->layout;
}

GPU_API void
gpu_cmd_set_blend_state(GPU_CmdBuf *cb, GPU_BlendState *state)
{
    // NOTE(sa): In Vulkan 1.3, blend state is baked into PSO. In a full
    // "No Graphics API" impl, this would use VK_EXT_extended_dynamic_state3.
    // For now, we store the state for pipeline recreation if needed.
    (void)cb;
    (void)state;
}

GPU_API void
gpu_cmd_set_depth_stencil_state(GPU_CmdBuf *cb, GPU_DepthStencilState *state)
{
    // NOTE(sa): In Vulkan 1.3, depth testing is baked into the pipeline unless
    // VK_EXT_extended_dynamic_state is enabled. We keep depth test & write enabled
    // by default with LESS_OR_EQUAL comparison.
    (void)cb;
    (void)state;
}

GPU_API void
gpu_cmd_set_viewport(GPU_CmdBuf *cb, F32 x, F32 y, F32 w, F32 h, F32 min_depth, F32 max_depth)
{
    VkViewport vp = { x, y, w, h, min_depth, max_depth };
    cb->device->vk.vkCmdSetViewport(cb->vk_cb, 0, 1, &vp);
}

GPU_API void
gpu_cmd_set_scissor(GPU_CmdBuf *cb, S32 x, S32 y, U32 w, U32 h)
{
    VkRect2D sc = { { x, y }, { w, h } };
    cb->device->vk.vkCmdSetScissor(cb->vk_cb, 0, 1, &sc);
}

////////////////////////////////
//~ sa: Rendering (Dynamic Rendering, Vulkan 1.3)

GPU_API void
gpu_cmd_begin_rendering(GPU_CmdBuf *cb,
                         GPU_Texture *color_target,
                         GPU_Texture *depth_target,
                         U32 width, U32 height)
{
    GPU_Device *dev = cb->device;

    // Transition color and depth attachments to optimal layouts
    VkImageMemoryBarrier2 barriers[2];
    U32 barrier_count = 0;

    if (color_target) {
        GPU_MemoryZeroStruct(&barriers[barrier_count]);
        barriers[barrier_count].sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
        barriers[barrier_count].srcStageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
        barriers[barrier_count].srcAccessMask = VK_ACCESS_2_MEMORY_READ_BIT | VK_ACCESS_2_MEMORY_WRITE_BIT;
        barriers[barrier_count].dstStageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;
        barriers[barrier_count].dstAccessMask = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT;
        barriers[barrier_count].oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        barriers[barrier_count].newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        barriers[barrier_count].srcQueueFamilyIndex = ~0u;
        barriers[barrier_count].dstQueueFamilyIndex = ~0u;
        barriers[barrier_count].image = color_target->image;
        barriers[barrier_count].subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        barriers[barrier_count].subresourceRange.levelCount = GPU_Max(color_target->desc.mip_levels, 1);
        barriers[barrier_count].subresourceRange.layerCount = 1;
        barrier_count += 1;
    }

    if (depth_target) {
        GPU_MemoryZeroStruct(&barriers[barrier_count]);
        barriers[barrier_count].sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
        barriers[barrier_count].srcStageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
        barriers[barrier_count].srcAccessMask = VK_ACCESS_2_MEMORY_READ_BIT | VK_ACCESS_2_MEMORY_WRITE_BIT;
        barriers[barrier_count].dstStageMask = VK_PIPELINE_STAGE_2_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_2_LATE_FRAGMENT_TESTS_BIT;
        barriers[barrier_count].dstAccessMask = VK_ACCESS_2_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT | VK_ACCESS_2_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
        barriers[barrier_count].oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        barriers[barrier_count].newLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
        barriers[barrier_count].srcQueueFamilyIndex = ~0u;
        barriers[barrier_count].dstQueueFamilyIndex = ~0u;
        barriers[barrier_count].image = depth_target->image;
        barriers[barrier_count].subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
        barriers[barrier_count].subresourceRange.levelCount = GPU_Max(depth_target->desc.mip_levels, 1);
        barriers[barrier_count].subresourceRange.layerCount = 1;
        barrier_count += 1;
    }

    if (barrier_count > 0) {
        VkDependencyInfo dep = {0};
        dep.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
        dep.imageMemoryBarrierCount = barrier_count;
        dep.pImageMemoryBarriers = barriers;
        dev->vk.vkCmdPipelineBarrier2(cb->vk_cb, &dep);
    }

    VkRenderingAttachmentInfo color_att = {0};
    color_att.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;
    color_att.loadOp = 1;  // VK_ATTACHMENT_LOAD_OP_CLEAR
    color_att.storeOp = 0; // VK_ATTACHMENT_STORE_OP_STORE
    color_att.clearValue.float32[0] = 0.10f; // dark navy/slate clear color
    color_att.clearValue.float32[1] = 0.12f;
    color_att.clearValue.float32[2] = 0.16f;
    color_att.clearValue.float32[3] = 1.0f;

    if (color_target) {
        color_att.imageView = color_target->image_view;
        color_att.imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    }

    VkRenderingAttachmentInfo depth_att = {0};
    depth_att.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;
    depth_att.loadOp = 1;  // VK_ATTACHMENT_LOAD_OP_CLEAR
    depth_att.storeOp = 0; // VK_ATTACHMENT_STORE_OP_STORE
    depth_att.clearValue.float32[0] = 1.0f; // clear depth to 1.0

    if (depth_target) {
        depth_att.imageView = depth_target->image_view;
        depth_att.imageLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    }

    VkRenderingInfo info = {0};
    info.sType = VK_STRUCTURE_TYPE_RENDERING_INFO;
    info.renderArea.extent.width = width;
    info.renderArea.extent.height = height;
    info.layerCount = 1;

    if (color_target) {
        info.colorAttachmentCount = 1;
        info.pColorAttachments = &color_att;
    }
    if (depth_target) {
        info.pDepthAttachment = &depth_att;
    }

    cb->device->vk.vkCmdBeginRendering(cb->vk_cb, &info);
}

GPU_API void
gpu_cmd_end_rendering(GPU_CmdBuf *cb)
{
    cb->device->vk.vkCmdEndRendering(cb->vk_cb);
}

////////////////////////////////
//~ sa: Compute Dispatch

GPU_API void
gpu_cmd_dispatch(GPU_CmdBuf *cb, U64 data_gpu, GPU_UVec3 grid)
{
    // Push the root data pointer via push constants
    U64 push_data[2] = { data_gpu, 0 };
    cb->device->vk.vkCmdPushConstants(cb->vk_cb, cb->bound_layout,
                                       VK_SHADER_STAGE_ALL, 0,
                                       sizeof(push_data), push_data);
    cb->device->vk.vkCmdDispatch(cb->vk_cb, grid.x, grid.y, grid.z);
}

GPU_API void
gpu_cmd_dispatch_indirect(GPU_CmdBuf *cb, U64 data_gpu, U64 grid_args_gpu)
{
    U64 push_data[2] = { data_gpu, 0 };
    cb->device->vk.vkCmdPushConstants(cb->vk_cb, cb->bound_layout,
                                       VK_SHADER_STAGE_ALL, 0,
                                       sizeof(push_data), push_data);
    // NOTE(sa): Indirect dispatch requires a VkBuffer + offset.
    // We need to find the buffer that contains this device address.
    // In a real implementation, we'd maintain an address->buffer map.
    // For now, this is a placeholder that requires the user to use
    // gpu_cmd_dispatch() with explicit dimensions instead.
    (void)grid_args_gpu;
    GPU_ASSERT(0 && "gpu_cmd_dispatch_indirect: not yet implemented - use gpu_cmd_dispatch");
}

////////////////////////////////
//~ sa: Draw Calls

GPU_API void
gpu_cmd_draw(GPU_CmdBuf *cb,
             U64 vertex_data_gpu,
             U64 pixel_data_gpu,
             U32 vertex_count,
             U32 instance_count)
{
    U64 push_data[2] = { vertex_data_gpu, pixel_data_gpu };
    cb->device->vk.vkCmdPushConstants(cb->vk_cb, cb->bound_layout,
                                       VK_SHADER_STAGE_ALL, 0,
                                       sizeof(push_data), push_data);
    cb->device->vk.vkCmdDraw(cb->vk_cb, vertex_count, instance_count, 0, 0);
}

GPU_API void
gpu_cmd_draw_indexed(GPU_CmdBuf *cb,
                      U64 vertex_data_gpu,
                      U64 pixel_data_gpu,
                      U64 index_buffer_gpu,
                      U32 index_count,
                      U32 instance_count)
{
    // Push vertex + pixel root pointers
    U64 push_data[2] = { vertex_data_gpu, pixel_data_gpu };
    cb->device->vk.vkCmdPushConstants(cb->vk_cb, cb->bound_layout,
                                       VK_SHADER_STAGE_ALL, 0,
                                       sizeof(push_data), push_data);

    // NOTE(sa): In the "No Graphics API" model, index buffers are bound via
    // 64-bit device address. In Vulkan, we need the actual VkBuffer handle.
    // For this implementation, users should pre-bind the index buffer via
    // the GPU_Alloc that contains it.
    (void)index_buffer_gpu;

    cb->device->vk.vkCmdDrawIndexed(cb->vk_cb, index_count, instance_count, 0, 0, 0);
}

GPU_API void
gpu_cmd_draw_indexed_indirect(GPU_CmdBuf *cb,
                               U64 vertex_data_gpu,
                               U64 pixel_data_gpu,
                               U64 indirect_args_gpu)
{
    U64 push_data[2] = { vertex_data_gpu, pixel_data_gpu };
    cb->device->vk.vkCmdPushConstants(cb->vk_cb, cb->bound_layout,
                                       VK_SHADER_STAGE_ALL, 0,
                                       sizeof(push_data), push_data);
    (void)indirect_args_gpu;
    GPU_ASSERT(0 && "gpu_cmd_draw_indexed_indirect: requires buffer tracking");
}

GPU_API void
gpu_cmd_draw_indexed_indirect_count(GPU_CmdBuf *cb,
                                     U64 vertex_data_gpu,
                                     U64 pixel_data_gpu,
                                     U64 indirect_args_gpu,
                                     U64 count_gpu,
                                     U32 max_draw_count)
{
    U64 push_data[2] = { vertex_data_gpu, pixel_data_gpu };
    cb->device->vk.vkCmdPushConstants(cb->vk_cb, cb->bound_layout,
                                       VK_SHADER_STAGE_ALL, 0,
                                       sizeof(push_data), push_data);
    (void)indirect_args_gpu;
    (void)count_gpu;
    (void)max_draw_count;
    GPU_ASSERT(0 && "gpu_cmd_draw_indexed_indirect_count: requires buffer tracking");
}

////////////////////////////////
//~ sa: Memory Commands

GPU_API void
gpu_cmd_copy(GPU_CmdBuf *cb, U64 dst_gpu, U64 src_gpu, U64 size)
{
    // NOTE(sa): buffer-to-buffer copy requires VkBuffer handles.
    // In a true "No Graphics API", the driver would resolve device addresses
    // to buffer handles internally. Here we assert; users should work with
    // GPU_Alloc objects directly.
    (void)cb; (void)dst_gpu; (void)src_gpu; (void)size;
    GPU_ASSERT(0 && "gpu_cmd_copy: use gpu_cmd_copy_buffer for GPU_Alloc-based copies");
}

GPU_API void
gpu_cmd_copy_to_texture(GPU_CmdBuf *cb, GPU_Texture *dst, GPU_Alloc *src_upload)
{
    GPU_Device *dev = cb->device;

    // Transition image to TRANSFER_DST
    VkImageMemoryBarrier2 barrier = {0};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
    barrier.srcStageMask = VK_PIPELINE_STAGE_2_NONE;
    barrier.srcAccessMask = VK_ACCESS_2_NONE;
    barrier.dstStageMask = VK_PIPELINE_STAGE_2_TRANSFER_BIT;
    barrier.dstAccessMask = VK_ACCESS_2_TRANSFER_WRITE_BIT;
    barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    barrier.srcQueueFamilyIndex = ~0u;
    barrier.dstQueueFamilyIndex = ~0u;
    barrier.image = dst->image;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.levelCount = GPU_Max(dst->desc.mip_levels, 1);
    barrier.subresourceRange.layerCount = 1;

    VkDependencyInfo dep = {0};
    dep.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
    dep.imageMemoryBarrierCount = 1;
    dep.pImageMemoryBarriers = &barrier;
    dev->vk.vkCmdPipelineBarrier2(cb->vk_cb, &dep);

    // Copy buffer to image
    VkBufferImageCopy region = {0};
    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.layerCount = 1;
    region.imageExtent.width = dst->desc.width;
    region.imageExtent.height = dst->desc.height;
    region.imageExtent.depth = GPU_Max(dst->desc.depth, 1);

    dev->vk.vkCmdCopyBufferToImage(cb->vk_cb, src_upload->buffer, dst->image,
                                    VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                                    1, &region);

    // Transition to SHADER_READ_ONLY
    barrier.srcStageMask = VK_PIPELINE_STAGE_2_TRANSFER_BIT;
    barrier.srcAccessMask = VK_ACCESS_2_TRANSFER_WRITE_BIT;
    barrier.dstStageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
    barrier.dstAccessMask = VK_ACCESS_2_SHADER_READ_BIT;
    barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    dev->vk.vkCmdPipelineBarrier2(cb->vk_cb, &dep);
}

GPU_API void
gpu_cmd_copy_texture_to_buffer(GPU_CmdBuf *cb, GPU_Alloc *dst_buffer, GPU_Texture *src_texture)
{
    GPU_Device *dev = cb->device;

    // Transition image to TRANSFER_SRC
    VkImageMemoryBarrier2 barrier = {0};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
    barrier.srcStageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
    barrier.srcAccessMask = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_2_MEMORY_WRITE_BIT;
    barrier.dstStageMask = VK_PIPELINE_STAGE_2_TRANSFER_BIT;
    barrier.dstAccessMask = VK_ACCESS_2_TRANSFER_READ_BIT;
    barrier.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    barrier.srcQueueFamilyIndex = ~0u;
    barrier.dstQueueFamilyIndex = ~0u;
    barrier.image = src_texture->image;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.levelCount = GPU_Max(src_texture->desc.mip_levels, 1);
    barrier.subresourceRange.layerCount = 1;

    VkDependencyInfo dep = {0};
    dep.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
    dep.imageMemoryBarrierCount = 1;
    dep.pImageMemoryBarriers = &barrier;
    dev->vk.vkCmdPipelineBarrier2(cb->vk_cb, &dep);

    // Copy image to buffer
    VkBufferImageCopy region = {0};
    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.layerCount = 1;
    region.imageExtent.width = src_texture->desc.width;
    region.imageExtent.height = src_texture->desc.height;
    region.imageExtent.depth = GPU_Max(src_texture->desc.depth, 1);

    dev->vk.vkCmdCopyImageToBuffer(cb->vk_cb, src_texture->image,
                                   VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                                   dst_buffer->buffer,
                                   1, &region);
}

////////////////////////////////
//~ sa: Barriers (Coarse-Grained Queue Execution Dependencies)

GPU_API void
gpu_cmd_barrier(GPU_CmdBuf *cb,
                 U32 src_stage_mask,
                 U32 dst_stage_mask,
                 U32 hazard_mask)
{
    VkMemoryBarrier2 mem_barrier = {0};
    mem_barrier.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER_2;
    mem_barrier.srcStageMask = gpu__vk_stage_mask(src_stage_mask);
    mem_barrier.dstStageMask = gpu__vk_stage_mask(dst_stage_mask);

    // Access masks: broad read/write for coarse-grained barriers
    mem_barrier.srcAccessMask = VK_ACCESS_2_MEMORY_WRITE_BIT;
    mem_barrier.dstAccessMask = VK_ACCESS_2_MEMORY_READ_BIT | VK_ACCESS_2_MEMORY_WRITE_BIT;

    // Hazard-specific access bits
    if (hazard_mask & GPU_HazardFlags_Descriptors) {
        mem_barrier.dstAccessMask |= VK_ACCESS_2_SHADER_READ_BIT;
    }
    if (hazard_mask & GPU_HazardFlags_DrawArguments) {
        mem_barrier.dstStageMask |= VK_PIPELINE_STAGE_2_DRAW_INDIRECT_BIT;
        mem_barrier.dstAccessMask |= VK_ACCESS_2_MEMORY_READ_BIT;
    }

    VkDependencyInfo dep = {0};
    dep.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
    dep.memoryBarrierCount = 1;
    dep.pMemoryBarriers = &mem_barrier;

    cb->device->vk.vkCmdPipelineBarrier2(cb->vk_cb, &dep);
}

////////////////////////////////
//~ sa: Submission

GPU_API void
gpu_submit(GPU_Device *dev,
            GPU_Queue *queue,
            GPU_CmdBuf **cmd_bufs, U32 cmd_buf_count,
            GPU_Semaphore *signal_sem, U64 signal_value)
{
    // End all command buffers
    for (U32 i = 0; i < cmd_buf_count; i += 1) {
        VkResult r = dev->vk.vkEndCommandBuffer(cmd_bufs[i]->vk_cb);
        GPU_ASSERT(r == VK_SUCCESS);
    }

    // Build command buffer submit infos
    VkCommandBufferSubmitInfo cb_infos[16];
    GPU_ASSERT(cmd_buf_count <= GPU_ArrayCount(cb_infos));
    for (U32 i = 0; i < cmd_buf_count; i += 1) {
        GPU_MemoryZeroStruct(&cb_infos[i]);
        cb_infos[i].sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO;
        cb_infos[i].commandBuffer = cmd_bufs[i]->vk_cb;
    }

    // Signal semaphore
    VkSemaphoreSubmitInfo signal_info = {0};
    signal_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
    if (signal_sem) {
        signal_info.semaphore = signal_sem->vk_sem;
        signal_info.value = signal_value;
        signal_info.stageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
    }

    VkSubmitInfo2 submit = {0};
    submit.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2;
    submit.commandBufferInfoCount = cmd_buf_count;
    submit.pCommandBufferInfos = cb_infos;

    if (signal_sem) {
        submit.signalSemaphoreInfoCount = 1;
        submit.pSignalSemaphoreInfos = &signal_info;
    }

    VkResult r = dev->vk.vkQueueSubmit2(queue->vk_queue, 1, &submit, VK_NULL_HANDLE);
    GPU_ASSERT(r == VK_SUCCESS);

    // Free transient command buffer wrappers (Vulkan CB stays alive until pool reset)
    for (U32 i = 0; i < cmd_buf_count; i += 1) {
        GPU_FREE(cmd_bufs[i]);
    }
}

GPU_API void
gpu_queue_wait_idle(GPU_Device *dev, GPU_Queue *queue)
{
    dev->vk.vkQueueWaitIdle(queue->vk_queue);
    dev->vk.vkResetCommandPool(dev->device, queue->cmd_pool, 0);
}

GPU_API void
gpu_device_wait_idle(GPU_Device *dev)
{
    dev->vk.vkDeviceWaitIdle(dev->device);
}

////////////////////////////////
//~ sa: Swapchain & Presentation (Cross-Platform)

internal GPU_Swapchain *
gpu__swapchain_create_from_surface(GPU_Device *dev, VkSurfaceKHR surface, U32 width, U32 height)
{
    GPU_Swapchain *sc = (GPU_Swapchain *)GPU_MALLOC(sizeof(GPU_Swapchain));
    GPU_MemoryZeroStruct(sc);
    sc->device = dev;
    sc->surface = surface;
    sc->width = width;
    sc->height = height;

    // 1. Check surface support on graphics queue
    VkBool32 supported = 0;
    dev->vk.vkGetPhysicalDeviceSurfaceSupportKHR(dev->physical_device, dev->graphics_queue_family, sc->surface, &supported);
    GPU_ASSERT(supported && "Graphics queue does not support presentation to surface");

    // 2. Query formats
    U32 format_count = 0;
    dev->vk.vkGetPhysicalDeviceSurfaceFormatsKHR(dev->physical_device, sc->surface, &format_count, 0);
    struct {
        S32 format;
        S32 colorSpace;
    } formats[16];
    U32 actual_formats = GPU_Min(format_count, 16);
    dev->vk.vkGetPhysicalDeviceSurfaceFormatsKHR(dev->physical_device, sc->surface, &actual_formats, formats);

    S32 chosen_vk_format = formats[0].format;
    GPU_Format chosen_gpu_format = GPU_Format_B8G8R8A8_UNorm;

    for (U32 i = 0; i < actual_formats; i += 1) {
        if (formats[i].format == VK_FORMAT_B8G8R8A8_UNORM) {
            chosen_vk_format = VK_FORMAT_B8G8R8A8_UNORM;
            chosen_gpu_format = GPU_Format_B8G8R8A8_UNorm;
            break;
        } else if (formats[i].format == VK_FORMAT_R8G8B8A8_UNORM) {
            chosen_vk_format = VK_FORMAT_R8G8B8A8_UNORM;
            chosen_gpu_format = GPU_Format_R8G8B8A8_UNorm;
            break;
        }
    }
    sc->format = chosen_gpu_format;

    // 3. Query capabilities
    struct {
        U32 minImageCount;
        U32 maxImageCount;
        VkExtent2D currentExtent;
        VkExtent2D minImageExtent;
        VkExtent2D maxImageExtent;
        U32 maxImageArrayLayers;
        VkFlags supportedTransforms;
        VkFlags currentTransform;
        VkFlags supportedCompositeAlpha;
        VkFlags supportedUsageFlags;
    } caps;
    dev->vk.vkGetPhysicalDeviceSurfaceCapabilitiesKHR(dev->physical_device, sc->surface, &caps);

    U32 desired_images = caps.minImageCount + 1;
    if (caps.maxImageCount > 0 && desired_images > caps.maxImageCount) {
        desired_images = caps.maxImageCount;
    }

    VkExtent2D extent = { width, height };
    if (caps.currentExtent.width != 0xFFFFFFFF) {
        extent = caps.currentExtent;
        sc->width = extent.width;
        sc->height = extent.height;
    }

    // 4. Create Swapchain
    struct {
        VkStructureType sType;
        const void *pNext;
        VkFlags flags;
        VkSurfaceKHR surface;
        U32 minImageCount;
        S32 imageFormat;
        S32 imageColorSpace;
        VkExtent2D imageExtent;
        U32 imageArrayLayers;
        VkFlags imageUsage;
        S32 imageSharingMode;
        U32 queueFamilyIndexCount;
        const U32 *pQueueFamilyIndices;
        VkFlags preTransform;
        VkFlags compositeAlpha;
        S32 presentMode;
        VkBool32 clipped;
        VkSwapchainKHR oldSwapchain;
    } sw_ci = {
        .sType = 1000001000, // VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR
        .surface = sc->surface,
        .minImageCount = desired_images,
        .imageFormat = chosen_vk_format,
        .imageColorSpace = 0, // VK_COLOR_SPACE_SRGB_NONLINEAR_KHR
        .imageExtent = extent,
        .imageArrayLayers = 1,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
        .imageSharingMode = 0, // VK_SHARING_MODE_EXCLUSIVE
        .preTransform = caps.currentTransform,
        .compositeAlpha = 1, // VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR
        .presentMode = 2, // VK_PRESENT_MODE_FIFO_KHR (vsync)
        .clipped = VK_TRUE,
    };

    VkResult r = dev->vk.vkCreateSwapchainKHR(dev->device, &sw_ci, 0, &sc->swapchain);
    GPU_ASSERT(r == VK_SUCCESS && "Failed to create swapchain");

    // 5. Get Swapchain Images
    dev->vk.vkGetSwapchainImagesKHR(dev->device, sc->swapchain, &sc->image_count, 0);
    VkImage vk_images[8];
    sc->image_count = GPU_Min(sc->image_count, 8);
    dev->vk.vkGetSwapchainImagesKHR(dev->device, sc->swapchain, &sc->image_count, vk_images);

    // 6. Wrap swapchain images in GPU_Texture and create binary synchronization semaphores & fences
    for (U32 i = 0; i < sc->image_count; i += 1) {
        struct {
            VkStructureType sType;
            const void *pNext;
            VkFlags flags;
            VkImage image;
            S32 viewType;
            S32 format;
            VkComponentMapping components;
            VkImageSubresourceRange subresourceRange;
        } view_ci = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .image = vk_images[i],
            .viewType = VK_IMAGE_VIEW_TYPE_2D,
            .format = chosen_vk_format,
            .components = { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY,
                            VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY },
            .subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 },
        };

        VkImageView view = VK_NULL_HANDLE;
        dev->vk.vkCreateImageView(dev->device, &view_ci, 0, &view);
        GPU_ASSERT(view != VK_NULL_HANDLE);

        GPU_Texture *tex = (GPU_Texture *)GPU_MALLOC(sizeof(GPU_Texture));
        GPU_MemoryZeroStruct(tex);
        tex->image = vk_images[i];
        tex->image_view = view;
        tex->desc.width = sc->width;
        tex->desc.height = sc->height;
        tex->desc.depth = 1;
        tex->desc.mip_levels = 1;
        tex->desc.format = chosen_gpu_format;
        tex->desc.is_render_target = 1;
        tex->owns_memory = 0;
        sc->textures[i] = tex;

        // Binary semaphores for swapchain sync
        struct {
            VkStructureType sType;
            const void *pNext;
            VkFlags flags;
        } sem_ci = { .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };
        dev->vk.vkCreateSemaphore(dev->device, &sem_ci, 0, &sc->image_available_sems[i]);
        dev->vk.vkCreateSemaphore(dev->device, &sem_ci, 0, &sc->render_finished_sems[i]);

        // Fence for CPU-GPU frame synchronization (created signaled)
        struct {
            VkStructureType sType;
            const void *pNext;
            VkFlags flags;
        } fence_ci = {
            .sType = 8, // VK_STRUCTURE_TYPE_FENCE_CREATE_INFO
            .flags = 0x00000001, // VK_FENCE_CREATE_SIGNALED_BIT
        };
        dev->vk.vkCreateFence(dev->device, &fence_ci, 0, &sc->in_flight_fences[i]);
    }

    return sc;
}

GPU_API GPU_Swapchain *
gpu_swapchain_create_xcb(GPU_Device *dev, void *connection, U32 window, U32 width, U32 height)
{
    GPU_ASSERT(dev->surface_enabled && "Must set enable_surface = 1 in GPU_DeviceDesc to use swapchains");
    GPU_ASSERT(dev->vk.vkCreateXcbSurfaceKHR && "VK_KHR_xcb_surface not available on this platform/device");

    struct {
        VkStructureType sType;
        const void *pNext;
        VkFlags flags;
        void *connection;
        U32 window;
    } sci = {
        .sType = 1000005000, // VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR
        .connection = connection,
        .window = window,
    };
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    VkResult r = dev->vk.vkCreateXcbSurfaceKHR(dev->instance, &sci, 0, &surface);
    GPU_ASSERT(r == VK_SUCCESS && "Failed to create XCB surface");

    return gpu__swapchain_create_from_surface(dev, surface, width, height);
}

GPU_API GPU_Swapchain *
gpu_swapchain_create_win32(GPU_Device *dev, void *hinstance, void *hwnd, U32 width, U32 height)
{
    GPU_ASSERT(dev->surface_enabled && "Must set enable_surface = 1 in GPU_DeviceDesc to use swapchains");
    GPU_ASSERT(dev->vk.vkCreateWin32SurfaceKHR && "VK_KHR_win32_surface not available on this platform/device");

#if defined(GPU_OS_WINDOWS)
    if (!hinstance) {
        hinstance = (void *)GetModuleHandleA(0);
    }
#endif

    struct {
        VkStructureType sType;
        const void *pNext;
        VkFlags flags;
        void *hinstance;
        void *hwnd;
    } sci = {
        .sType = 1000009000, // VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR
        .hinstance = hinstance,
        .hwnd = hwnd,
    };
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    VkResult r = dev->vk.vkCreateWin32SurfaceKHR(dev->instance, &sci, 0, &surface);
    GPU_ASSERT(r == VK_SUCCESS && "Failed to create Win32 surface");

    return gpu__swapchain_create_from_surface(dev, surface, width, height);
}

GPU_API GPU_Swapchain *
gpu_swapchain_create(GPU_Device *device, const GPU_WindowHandle *window, U32 width, U32 height)
{
    if (!device || !window) return 0;
#if defined(GPU_OS_WINDOWS)
    return gpu_swapchain_create_win32(device, window->hinstance, window->hwnd, width, height);
#elif defined(GPU_OS_LINUX)
    return gpu_swapchain_create_xcb(device, window->connection, window->window, width, height);
#else
    return 0;
#endif
}

GPU_API void
gpu_swapchain_destroy(GPU_Device *dev, GPU_Swapchain *sc)
{
    if (!sc) return;
    dev->vk.vkDeviceWaitIdle(dev->device);

    for (U32 i = 0; i < sc->image_count; i += 1) {
        if (sc->frame_cmd_bufs[i]) {
            GPU_CmdBuf *old_cb = sc->frame_cmd_bufs[i];
            dev->vk.vkFreeCommandBuffers(dev->device, old_cb->queue->cmd_pool, 1, &old_cb->vk_cb);
            GPU_FREE(old_cb);
            sc->frame_cmd_bufs[i] = 0;
        }
        if (sc->in_flight_fences[i]) dev->vk.vkDestroyFence(dev->device, sc->in_flight_fences[i], 0);
        if (sc->image_available_sems[i]) dev->vk.vkDestroySemaphore(dev->device, sc->image_available_sems[i], 0);
        if (sc->render_finished_sems[i]) dev->vk.vkDestroySemaphore(dev->device, sc->render_finished_sems[i], 0);
        if (sc->textures[i]) {
            if (sc->textures[i]->image_view) dev->vk.vkDestroyImageView(dev->device, sc->textures[i]->image_view, 0);
            GPU_FREE(sc->textures[i]);
        }
    }

    if (sc->swapchain) dev->vk.vkDestroySwapchainKHR(dev->device, sc->swapchain, 0);
    if (sc->surface) dev->vk.vkDestroySurfaceKHR(dev->instance, sc->surface, 0);
    GPU_FREE(sc);
}

GPU_API GPU_Texture *
gpu_swapchain_acquire(GPU_Device *dev, GPU_Swapchain *sc)
{
    // Wait for the fence of the frame slot to ensure previous rendering on this slot is complete
    dev->vk.vkWaitForFences(dev->device, 1, &sc->in_flight_fences[sc->current_frame], VK_TRUE, ~(U64)0);
    dev->vk.vkResetFences(dev->device, 1, &sc->in_flight_fences[sc->current_frame]);

    // Safely free previous command buffer of this frame slot now that GPU execution has completed
    if (sc->frame_cmd_bufs[sc->current_frame]) {
        GPU_CmdBuf *old_cb = sc->frame_cmd_bufs[sc->current_frame];
        dev->vk.vkFreeCommandBuffers(dev->device, old_cb->queue->cmd_pool, 1, &old_cb->vk_cb);
        GPU_FREE(old_cb);
        sc->frame_cmd_bufs[sc->current_frame] = 0;
    }

    VkResult r = dev->vk.vkAcquireNextImageKHR(dev->device, sc->swapchain, ~(U64)0,
                                               sc->image_available_sems[sc->current_frame],
                                               VK_NULL_HANDLE,
                                               &sc->current_image_index);
    if (r != VK_SUCCESS && r != 1000001003 /* VK_SUBOPTIMAL_KHR */) {
        return 0;
    }
    return sc->textures[sc->current_image_index];
}

GPU_API void
gpu_swapchain_submit_and_present(GPU_Device *dev, GPU_Queue *queue, GPU_Swapchain *sc, GPU_CmdBuf *cb)
{
    // Transition swapchain image to PRESENT_SRC_KHR (1000001002)
    VkImageMemoryBarrier2 barrier = {0};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
    barrier.srcStageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;
    barrier.srcAccessMask = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT;
    barrier.dstStageMask = VK_PIPELINE_STAGE_2_BOTTOM_OF_PIPE_BIT;
    barrier.dstAccessMask = 0;
    barrier.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    barrier.newLayout = 1000001002; // VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
    barrier.srcQueueFamilyIndex = ~0u;
    barrier.dstQueueFamilyIndex = ~0u;
    barrier.image = sc->textures[sc->current_image_index]->image;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.levelCount = 1;
    barrier.subresourceRange.layerCount = 1;

    VkDependencyInfo dep = {
        .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
        .imageMemoryBarrierCount = 1,
        .pImageMemoryBarriers = &barrier,
    };
    dev->vk.vkCmdPipelineBarrier2(cb->vk_cb, &dep);

    dev->vk.vkEndCommandBuffer(cb->vk_cb);

    // Submit queue with wait on image_available and signal on render_finished
    VkSemaphoreSubmitInfo wait_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = sc->image_available_sems[sc->current_frame],
        .stageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
    };

    VkSemaphoreSubmitInfo signal_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = sc->render_finished_sems[sc->current_frame],
        .stageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
    };

    VkCommandBufferSubmitInfo cb_info = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO,
        .commandBuffer = cb->vk_cb,
    };

    VkSubmitInfo2 submit_info = {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
        .waitSemaphoreInfoCount = 1,
        .pWaitSemaphoreInfos = &wait_info,
        .commandBufferInfoCount = 1,
        .pCommandBufferInfos = &cb_info,
        .signalSemaphoreInfoCount = 1,
        .pSignalSemaphoreInfos = &signal_info,
    };

    dev->vk.vkQueueSubmit2(queue->vk_queue, 1, &submit_info, sc->in_flight_fences[sc->current_frame]);

    // Present
    struct {
        VkStructureType sType;
        const void *pNext;
        U32 waitSemaphoreCount;
        const VkSemaphore *pWaitSemaphores;
        U32 swapchainCount;
        const VkSwapchainKHR *pSwapchains;
        const U32 *pImageIndices;
        VkResult *pResults;
    } present_info = {
        .sType = 1000001001, // VK_STRUCTURE_TYPE_PRESENT_INFO_KHR
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &sc->render_finished_sems[sc->current_frame],
        .swapchainCount = 1,
        .pSwapchains = &sc->swapchain,
        .pImageIndices = &sc->current_image_index,
    };

    dev->vk.vkQueuePresentKHR(queue->vk_queue, &present_info);

    // Track command buffer for this frame slot so it can be freed after fence completes next cycle
    sc->frame_cmd_bufs[sc->current_frame] = cb;
    sc->current_frame = (sc->current_frame + 1) % sc->image_count;
}

GPU_API GPU_Format
gpu_swapchain_format(GPU_Swapchain *sc)
{
    return sc->format;
}

#endif // GPU_IMPLEMENTATION_GUARD
#endif // GPU_IMPLEMENTATION
