// example.c - Minimal "No Graphics API" usage example
//
// Demonstrates the core concepts from Sebastian Aaltonen's "No Graphics API":
//   1. CUDA-style gpuMalloc with direct CPU-GPU memory mapping
//   2. Single root pointer passed to shaders via push constants
//   3. Timeline semaphore synchronization
//   4. Coarse-grained barriers (no per-resource state tracking)
//
// BUILD: cc -o example example.c -ldl -lm
// (No Vulkan SDK headers needed - everything is loaded at runtime)

#define GPU_IMPLEMENTATION
#include "gpu.h"

#include <stdio.h>
#include <string.h>

int
main(void)
{
    printf("=== No Graphics API - Vulkan Example ===\n\n");

    //- Create device (Vulkan 1.3 required)
    GPU_DeviceDesc device_desc = {
        .enable_validation = 0,
        .app_name = "no-gfx-api-example",
    };

    GPU_Device *device = gpu_device_create(&device_desc);
    printf("[OK] Device created\n");

    //- Create queue
    GPU_Queue *queue = gpu_queue_create(device);
    printf("[OK] Queue created\n");

    //- Allocate DEFAULT memory (CPU writes, GPU reads - UMA/ReBAR)
    // This is the core "gpuMalloc" concept: no VkBuffer creation boilerplate,
    // no memory type queries - just malloc and get both CPU + GPU addresses.
    U64 alloc_size = GPU_KB(64);
    GPU_Alloc *default_alloc = gpu_malloc(device, alloc_size, GPU_MemoryKind_Default);

    void *cpu_ptr   = gpu_alloc_cpu_ptr(default_alloc);
    U64   gpu_addr  = gpu_alloc_device_addr(default_alloc);

    printf("[OK] DEFAULT memory: %llu bytes\n", (unsigned long long)alloc_size);
    printf("     CPU ptr:  %p\n", cpu_ptr);
    printf("     GPU addr: 0x%llx\n", (unsigned long long)gpu_addr);

    //- Write data directly from CPU (no staging buffer, no upload commands!)
    // On UMA/ReBAR systems, the GPU sees this immediately.
    typedef struct {
        F32 color[4];
        U64 vertex_buffer_ptr;
        U32 vertex_count;
        U32 padding;
    } DrawData;

    DrawData *draw_data = (DrawData *)cpu_ptr;
    draw_data->color[0] = 1.0f;
    draw_data->color[1] = 0.5f;
    draw_data->color[2] = 0.0f;
    draw_data->color[3] = 1.0f;
    draw_data->vertex_count = 3;

    // The GPU virtual address of this struct is what gets passed to shaders
    // as the single root pointer - replacing all descriptor sets/tables.
    U64 draw_data_gpu = gpu_host_to_device_ptr(device, default_alloc, draw_data);
    printf("[OK] Draw data written at GPU addr: 0x%llx\n", (unsigned long long)draw_data_gpu);

    //- Allocate GPU-only memory (private VRAM with DCC/compression)
    GPU_Alloc *gpu_alloc = gpu_malloc(device, GPU_KB(256), GPU_MemoryKind_GpuOnly);
    printf("[OK] GPU-ONLY memory: %llu bytes at GPU addr 0x%llx\n",
           (unsigned long long)gpu_alloc_size(gpu_alloc),
           (unsigned long long)gpu_alloc_device_addr(gpu_alloc));

    //- Allocate readback memory (GPU writes, CPU reads)
    GPU_Alloc *readback = gpu_malloc(device, GPU_KB(4), GPU_MemoryKind_Readback);
    printf("[OK] READBACK memory: %llu bytes\n", (unsigned long long)gpu_alloc_size(readback));

    //- Create timeline semaphore
    GPU_Semaphore *sem = gpu_semaphore_create(device, 0);
    printf("[OK] Timeline semaphore created (initial value: 0)\n");

    //- Create depth stencil state (dynamic - no PSO explosion!)
    GPU_DepthStencilState *depth_read_write = gpu_depth_stencil_state_create(device,
        GPU_DepthFlags_Read | GPU_DepthFlags_Write);
    GPU_DepthStencilState *depth_read_only = gpu_depth_stencil_state_create(device,
        GPU_DepthFlags_Read);
    printf("[OK] Dynamic depth-stencil states created\n");

    //- Record a command buffer with a barrier
    // Demonstrates coarse-grained barriers (no per-resource state tracking)
    {
        GPU_CmdBuf *cb = gpu_cmd_begin(device, queue);

        // After writing descriptors from CPU, invalidate sampler descriptor caches
        gpu_cmd_barrier(cb,
                        GPU_StageFlags_Transfer,
                        GPU_StageFlags_All,
                        GPU_HazardFlags_Descriptors);

        // Submit with timeline semaphore signal
        GPU_CmdBuf *cbs[] = { cb };
        gpu_submit(device, queue, cbs, 1, sem, 1);
    }

    // CPU-side wait on timeline semaphore
    gpu_semaphore_wait(device, sem, 1);
    U64 sem_value = gpu_semaphore_query(device, sem);
    printf("[OK] Timeline semaphore reached value: %llu\n", (unsigned long long)sem_value);

    //- Texture creation example
    GPU_TextureDesc tex_desc = {
        .width = 256,
        .height = 256,
        .depth = 1,
        .mip_levels = 1,
        .format = GPU_Format_R8G8B8A8_UNorm,
        .is_render_target = 1,
    };

    GPU_TextureSizeAlign tex_sa = gpu_texture_size_align(device, &tex_desc);
    printf("[OK] Texture 256x256 RGBA8: requires %llu bytes, align %llu\n",
           (unsigned long long)tex_sa.size,
           (unsigned long long)tex_sa.align);

    // Create texture (self-allocating in private VRAM)
    GPU_Texture *texture = gpu_texture_create(device, &tex_desc, 0);
    printf("[OK] Texture created\n");

    // Get 256-bit descriptor blob (for bindless descriptor heap)
    GPU_DescriptorBlob blob = gpu_texture_descriptor_blob(device, texture);
    printf("[OK] Descriptor blob: [0x%llx, 0x%llx, 0x%llx, 0x%llx]\n",
           (unsigned long long)blob.data[0],
           (unsigned long long)blob.data[1],
           (unsigned long long)blob.data[2],
           (unsigned long long)blob.data[3]);

    //- Upload texture data via staging buffer
    {
        // Allocate staging in DEFAULT memory
        U64 tex_data_size = 256 * 256 * 4; // RGBA8
        GPU_Alloc *staging = gpu_malloc(device, tex_data_size, GPU_MemoryKind_Default);

        // Fill with a gradient pattern directly via CPU pointer
        U8 *pixels = (U8 *)gpu_alloc_cpu_ptr(staging);
        for (U32 y = 0; y < 256; y += 1) {
            for (U32 x = 0; x < 256; x += 1) {
                U32 idx = (y * 256 + x) * 4;
                pixels[idx + 0] = (U8)x;       // R
                pixels[idx + 1] = (U8)y;       // G
                pixels[idx + 2] = 128;          // B
                pixels[idx + 3] = 255;          // A
            }
        }

        // Record upload commands
        GPU_CmdBuf *cb = gpu_cmd_begin(device, queue);
        gpu_cmd_copy_to_texture(cb, texture, staging);

        // Coarse barrier: transfer -> all stages
        gpu_cmd_barrier(cb, GPU_StageFlags_Transfer, GPU_StageFlags_All, GPU_HazardFlags_None);

        GPU_CmdBuf *cbs[] = { cb };
        gpu_submit(device, queue, cbs, 1, sem, 2);
        gpu_semaphore_wait(device, sem, 2);

        gpu_free(device, staging);
        printf("[OK] Texture data uploaded\n");
    }

    //- Cleanup
    gpu_texture_destroy(device, texture);
    gpu_depth_stencil_state_destroy(device, depth_read_write);
    gpu_depth_stencil_state_destroy(device, depth_read_only);
    gpu_semaphore_destroy(device, sem);
    gpu_free(device, readback);
    gpu_free(device, gpu_alloc);
    gpu_free(device, default_alloc);
    gpu_queue_destroy(device, queue);
    gpu_device_destroy(device);

    printf("\n[OK] All resources cleaned up. Done!\n");
    return 0;
}
