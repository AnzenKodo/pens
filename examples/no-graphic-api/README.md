# No Graphics API (Vulkan Backend)

A pure, zero-dependency C library implementing the **"No Graphics API"** design proposed by [Sebastian Aaltonen](https://www.sebastianaaltonen.com/blog/no-graphics-api) (2025), written in the **Sean Barrett (`stb`) & Ryan Fleury (`raddebugger`)** codebase style.

---

## Architecture & Motivation

Traditional modern graphics APIs (DirectX 12, Vulkan, Metal) were designed a decade ago around explicit CPU-side state micromanagement:
- **Monolithic Pipeline State Objects (PSOs):** Generating millions of state permutations, leading to runtime shader compilation stutter and massive disk shader caches.
- **Root Signatures & Descriptor Tables:** Complicated CPU binding models incompatible with how modern GPUs actually execute code.
- **Per-Resource State Tracking:** Fine-grained barriers that force the CPU to guess GPU memory access patterns.

### The Hardware Reality

Modern GPUs (AMD RDNA 3+, NVIDIA Ada/Blackwell, Apple Silicon, Qualcomm Adreno, ARM Immortalis) are **SIMD Von Neumann processors**:
1. **64-bit Virtual Addresses:** Pointers can be stored and dereferenced directly in shaders via standard 64-bit memory loads.
2. **PCIe ReBAR & Unified Memory (UMA):** The CPU can map GPU memory directly and write to it at full PCIe bus speed without staging buffers.
3. **Hardware Descriptor Blobs:** Modern GPUs represent texture descriptors as homogeneous **256-bit (32-byte) blobs** in regular GPU memory.
4. **Coherent Cache Hierarchies:** Most caches are coherent; only internal sampler descriptor caches and indirect argument caches need manual invalidation.

---

## Aaltonen's Proposed Core Primitives

| Traditional Vulkan / DX12 | "No Graphics API" | How `gpu.h` Implements It |
| :--- | :--- | :--- |
| `VkBuffer`, `VkDeviceMemory`, memory type queries, heaps | `gpuMalloc` / `gpuFree` | CUDA-style allocator returning CPU pointer + 64-bit GPU virtual address (`VkDeviceAddress`). |
| Descriptor Sets, Tables, Root Signatures | **Single Root Pointer** | A single 64-bit GPU pointer passed to shaders via push constants; shaders cast it to user struct and dereference memory directly. |
| Descriptor Pools, Descriptor Sets | **Bindless Descriptor Blobs** | Homogeneous array of 256-bit (`uint64[4]`) descriptor blobs in memory indexed by a 32-bit integer. |
| Monolithic PSOs (Blend + Raster + Shaders) | **Shader Objects + Dynamic State** | Independent shader stages, dynamic depth/stencil, dynamic rasterizer. Blending is programmable via framebuffer fetch. |
| Per-Resource Barriers (`VkImageMemoryBarrier`) | **Coarse Queue Barriers** | Stage-to-stage execution dependencies + non-coherent cache invalidation flags (`HAZARD_DESCRIPTORS`, `HAZARD_DRAW_ARGUMENTS`). |
| Fences, Semaphores, Events | **Timeline Semaphores** | Single monotonic 64-bit integer timeline semaphore for all CPU-GPU synchronization. |
| Command Pool Recycling & Lifecycles | **Transient Command Buffers** | Allocated immediately before recording, submitted, and automatically recycled. |

---

## Codebase Style (Ryan Fleury & Sean Barrett)

The library strictly adheres to the handmade programming style used in [EpicGames/raddebugger](https://github.com/EpicGamesExt/raddebugger):

- **Single-Header Library:** `gpu.h` contains both declarations and the implementation behind `#define GPU_IMPLEMENTATION`.
- **Zero External Dependencies:** No `<vulkan/vulkan.h>` header needed! `libvulkan.so` is loaded dynamically at runtime via `dlopen`/`dlsym`.
- **Type Conventions:** `U8`, `U16`, `U32`, `U64`, `S8`, `S16`, `S32`, `S64`, `B32`, `F32`, `F64`.
- **Codebase Keywords:** `internal` (static function), `global` (static variable), `local_persist` (static local).
- **Macro Design:** `GPU_ArrayCount`, `GPU_Min`, `GPU_Max`, `GPU_Clamp`, `GPU_AlignUp`, `GPU_KB`, `GPU_MB`, `GPU_GB`.
- **Comment Sections:** Clean `////////////////////////////////` and `//~ prefix: Title` dividers throughout.
- **Configurable Allocation & Asserts:** Customizable via `#define GPU_MALLOC`, `GPU_FREE`, `GPU_ASSERT`.

---

## Memory Kinds (`GPU_MemoryKind`)

```c
typedef enum GPU_MemoryKind {
    GPU_MemoryKind_Default,   // CPU-mapped, write-combined GPU memory (UMA / ReBAR). CPU writes, GPU reads.
    GPU_MemoryKind_GpuOnly,   // Private high-bandwidth VRAM (supports DCC/lossless compression).
    GPU_MemoryKind_Readback,  // GPU writes, CPU reads back (cached on host).
} GPU_MemoryKind;
```

---

## Quick Start Example

### 1. Build & Run

```bash
chmod +x build.sh
./build.sh
./example
```

### 2. Basic Code Example

```c
#define GPU_IMPLEMENTATION
#include "gpu.h"

int main(void) {
    // 1. Initialize device & queue
    GPU_DeviceDesc desc = { .app_name = "MyEngine" };
    GPU_Device *device = gpu_device_create(&desc);
    GPU_Queue  *queue  = gpu_queue_create(device);

    // 2. CUDA-style gpuMalloc: direct CPU and GPU access
    GPU_Alloc *mem = gpu_malloc(device, GPU_KB(64), GPU_MemoryKind_Default);
    void *cpu_ptr  = gpu_alloc_cpu_ptr(mem);
    U64   gpu_ptr  = gpu_alloc_device_addr(mem);

    // 3. Write data directly from CPU (no staging buffer or upload commands required on UMA/ReBAR)
    struct MyUniforms {
        float camera_matrix[16];
        uint64_t vertex_buffer_gpu_ptr;
        uint32_t texture_index;
    } *uniforms = (struct MyUniforms *)cpu_ptr;
    uniforms->texture_index = 42;

    // 4. Record transient command buffer
    GPU_CmdBuf *cb = gpu_cmd_begin(device, queue);

    // Invalidate descriptor cache after CPU descriptor updates
    gpu_cmd_barrier(cb, GPU_StageFlags_Transfer, GPU_StageFlags_All, GPU_HazardFlags_Descriptors);

    // 5. Submit with a monotonic timeline semaphore
    GPU_Semaphore *sem = gpu_semaphore_create(device, 0);
    GPU_CmdBuf *cbs[] = { cb };
    gpu_submit(device, queue, cbs, 1, sem, 1);

    // 6. Wait on host
    gpu_semaphore_wait(device, sem, 1);

    // 7. Clean up
    gpu_semaphore_destroy(device, sem);
    gpu_free(device, mem);
    gpu_queue_destroy(device, queue);
    gpu_device_destroy(device);
    return 0;
}
```

---

## 3D Three-Cube Example (`cube_example.c`)

Demonstrates a real-time interactive 3D rendering pipeline adhering to the "No Graphics API" philosophy with cross-platform native windowing:
- **Cross-Platform Window Presentation**:
  - **Windows (Win32)**: Native Win32 windowing (`CreateWindowExA`, `PeekMessageA`, `QueryPerformanceCounter`, `VK_KHR_win32_surface`).
  - **Linux (X11)**: Native XCB windowing (`<xcb/xcb.h>`, `-lxcb`, `clock_gettime`, `VK_KHR_xcb_surface`).
  - Interactive input handling (`ESC` / `q` to quit, window close buttons).
- **Vulkan WSI Swapchain Support**: Unified cross-platform swapchain API (`gpu_swapchain_create`, `gpu_swapchain_create_win32`, `gpu_swapchain_create_xcb`) with automatic format negotiation, binary semaphores, and in-flight fences.
- **Manual Vertex Pulling**: Empty vertex input state (`VkPipelineVertexInputStateCreateInfo`), pulling vertices from raw 64-bit GPU virtual addresses using `GL_EXT_buffer_reference`.
- **Single 64-Bit Root Pointer**: Push constants pass a single 64-bit device pointer directly to the vertex shader. The shader dereferences `root.mvp`, `root.model`, and `root.vertices_ptr` with zero descriptor overhead.
- **Dynamic Rendering & Dynamic Depth-Stencil**: Rendering 3 distinct cubes at different 3D positions and orientations into an 800x600 backbuffer and depth target (`D32_Float`).
- **Interactive Real-Time Animation**: Framerate-independent continuous rotation of all 3 cubes rendered at 60 FPS V-Synced.

### Build & Run 3 Cubes:

#### On Linux (Native XCB):
```bash
chmod +x build_cubes.sh
./build_cubes.sh
./cube_example
```

#### On Windows (MSVC cl.exe / Clang / GCC):
```bat
build_cubes.bat
cube_example.exe
```

#### Cross-compiling for Windows on Linux (MinGW-w64):
```bash
chmod +x build_cubes_win32.sh
./build_cubes_win32.sh
wine cube_example.exe
```

---

## References

1. **Sebastian Aaltonen:** [No Graphics API (Blog Post, 2025)](https://www.sebastianaaltonen.com/blog/no-graphics-api)
2. **SIGGRAPH 2026 Presentation:** *Reducing graphics API complexity: A clean slate API design for modern hardware* (Sebastian Aaltonen)
3. **RAD Debugger Codebase:** [EpicGamesExt/raddebugger](https://github.com/EpicGamesExt/raddebugger) (Ryan Fleury & RAD Tools)
4. **Vulkan 1.3 Core Specification:** Dynamic Rendering (`VK_KHR_dynamic_rendering`), Synchronization2 (`VK_KHR_synchronization2`), Buffer Device Address (`VK_KHR_buffer_device_address`), and Timeline Semaphores (`VK_KHR_timeline_semaphore`).
