#define VK_USE_PLATFORM_XCB_KHR
#include <vulkan/vulkan.h>
#include <xcb/xcb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 800
#define HEIGHT 600
#define APP_NAME "Vulkan Red Window"

VkInstance instance;
VkSurfaceKHR surface;
VkPhysicalDevice physical_device;
VkDevice device;
VkQueue queue;
VkSwapchainKHR swapchain;
uint32_t swapchain_image_count;
VkImage *swapchain_images;
VkImageView *image_views;
VkFramebuffer *framebuffers;
VkRenderPass render_pass;
VkCommandPool command_pool;
VkCommandBuffer *command_buffers;
VkSemaphore image_available_semaphore, render_finished_semaphore;
VkFence fence;

xcb_connection_t *connection;
xcb_window_t window;

void error(const char *msg) {
    perror(msg);
    exit(1);
}

void create_xcb_window() {
    connection = xcb_connect(NULL, NULL);
    if (xcb_connection_has_error(connection)) error("xcb_connect");

    const xcb_setup_t *setup = xcb_get_setup(connection);
    xcb_screen_t *screen = xcb_setup_roots_iterator(setup).data;

    window = xcb_generate_id(connection);

    uint32_t value_mask = XCB_CW_EVENT_MASK;
    uint32_t value_list[1] = { XCB_EVENT_MASK_STRUCTURE_NOTIFY | XCB_EVENT_MASK_EXPOSURE };

    xcb_create_window(connection, XCB_COPY_FROM_PARENT, window, screen->root,
                      0, 0, WIDTH, HEIGHT, 0,
                      XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual,
                      value_mask, value_list);

    xcb_change_property(connection, XCB_PROP_MODE_REPLACE, window,
                        XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8,
                        strlen(APP_NAME), APP_NAME);

    xcb_map_window(connection, window);
    xcb_flush(connection);
}

void create_instance() {
    VkApplicationInfo app_info = { .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                                   .pApplicationName = APP_NAME,
                                   .apiVersion = VK_API_VERSION_1_0 };

    const char *extensions[] = { VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_XCB_SURFACE_EXTENSION_NAME };

    VkInstanceCreateInfo create_info = { .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                                        .pApplicationInfo = &app_info,
                                        .enabledExtensionCount = 2,
                                        .ppEnabledExtensionNames = extensions };

    vkCreateInstance(&create_info, NULL, &instance);
}

void create_surface() {
    VkXcbSurfaceCreateInfoKHR surface_info = { .sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR,
                                               .connection = connection,
                                               .window = window };

    vkCreateXcbSurfaceKHR(instance, &surface_info, NULL, &surface);
}

void pick_physical_device() {
    uint32_t device_count;
    vkEnumeratePhysicalDevices(instance, &device_count, NULL);
    VkPhysicalDevice devices[device_count];
    vkEnumeratePhysicalDevices(instance, &device_count, devices);

    physical_device = devices[0];  // Pick first GPU (good enough for simple example)

    // Find graphics + present queue family
    uint32_t queue_family_count;
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, NULL);
    VkQueueFamilyProperties queue_families[queue_family_count];
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, queue_families);

    uint32_t graphics_family = -1, present_family = -1;
    for (uint32_t i = 0; i < queue_family_count; i++) {
        if (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) graphics_family = i;

        VkBool32 present_support;
        vkGetPhysicalDeviceSurfaceSupportKHR(physical_device, i, surface, &present_support);
        if (present_support) present_family = i;
    }

    // Assume graphics == present for simplicity (common on desktops)
}

void create_logical_device() {
    uint32_t queue_family = 0;  // Hardcode first family (graphics+present)

    float queue_priority = 1.0f;
    VkDeviceQueueCreateInfo queue_info = { .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
                                           .queueFamilyIndex = queue_family,
                                           .queueCount = 1,
                                           .pQueuePriorities = &queue_priority };

    const char *device_extensions[] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

    VkDeviceCreateInfo device_info = { .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
                                       .queueCreateInfoCount = 1,
                                       .pQueueCreateInfos = &queue_info,
                                       .enabledExtensionCount = 1,
                                       .ppEnabledExtensionNames = device_extensions };

    vkCreateDevice(physical_device, &device_info, NULL, &device);

    vkGetDeviceQueue(device, queue_family, 0, &queue);
}

void create_swapchain() {
    VkSurfaceCapabilitiesKHR caps;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical_device, surface, &caps);

    VkExtent2D extent = { WIDTH, HEIGHT };

    uint32_t format_count;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device, surface, &format_count, NULL);
    VkSurfaceFormatKHR formats[format_count];
    vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device, surface, &format_count, formats);

    VkSurfaceFormatKHR format = formats[0];  // Pick first

    VkSwapchainCreateInfoKHR swap_info = { .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
                                           .surface = surface,
                                           .minImageCount = caps.minImageCount + 1,
                                           .imageFormat = format.format,
                                           .imageColorSpace = format.colorSpace,
                                           .imageExtent = extent,
                                           .imageArrayLayers = 1,
                                           .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
                                           .preTransform = caps.currentTransform,
                                           .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
                                           .presentMode = VK_PRESENT_MODE_FIFO_KHR,
                                           .clipped = VK_TRUE };

    vkCreateSwapchainKHR(device, &swap_info, NULL, &swapchain);

    vkGetSwapchainImagesKHR(device, swapchain, &swapchain_image_count, NULL);
    swapchain_images = malloc(swapchain_image_count * sizeof(VkImage));
    vkGetSwapchainImagesKHR(device, swapchain, &swapchain_image_count, swapchain_images);
}

void create_image_views_and_framebuffers() {
    image_views = malloc(swapchain_image_count * sizeof(VkImageView));

    for (uint32_t i = 0; i < swapchain_image_count; i++) {
        VkImageViewCreateInfo view_info = { .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
                                            .image = swapchain_images[i],
                                            .viewType = VK_IMAGE_VIEW_TYPE_2D,
                                            .format = VK_FORMAT_B8G8R8A8_SRGB,  // Common format
                                            .subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                                            .subresourceRange.levelCount = 1,
                                            .subresourceRange.layerCount = 1 };

        vkCreateImageView(device, &view_info, NULL, &image_views[i]);
    }

    // Simple render pass for clear
    VkAttachmentDescription attachment = { .format = VK_FORMAT_B8G8R8A8_SRGB,
                                           .samples = VK_SAMPLE_COUNT_1_BIT,
                                           .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
                                           .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
                                           .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                                           .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
                                           .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
                                           .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR };

    VkAttachmentReference color_ref = { 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };

    VkSubpassDescription subpass = { .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
                                     .colorAttachmentCount = 1,
                                     .pColorAttachments = &color_ref };

    VkRenderPassCreateInfo rp_info = { .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
                                       .attachmentCount = 1,
                                       .pAttachments = &attachment,
                                       .subpassCount = 1,
                                       .pSubpasses = &subpass };

    vkCreateRenderPass(device, &rp_info, NULL, &render_pass);

    framebuffers = malloc(swapchain_image_count * sizeof(VkFramebuffer));

    for (uint32_t i = 0; i < swapchain_image_count; i++) {
        VkFramebufferCreateInfo fb_info = { .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
                                            .renderPass = render_pass,
                                            .attachmentCount = 1,
                                            .pAttachments = &image_views[i],
                                            .width = WIDTH,
                                            .height = HEIGHT,
                                            .layers = 1 };

        vkCreateFramebuffer(device, &fb_info, NULL, &framebuffers[i]);
    }
}

void create_command_buffers() {
    VkCommandPoolCreateInfo pool_info = { .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
                                          .queueFamilyIndex = 0 };

    vkCreateCommandPool(device, &pool_info, NULL, &command_pool);

    command_buffers = malloc(swapchain_image_count * sizeof(VkCommandBuffer));

    VkCommandBufferAllocateInfo alloc_info = { .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
                                               .commandPool = command_pool,
                                               .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
                                               .commandBufferCount = swapchain_image_count };

    vkAllocateCommandBuffers(device, &alloc_info, command_buffers);

    for (uint32_t i = 0; i < swapchain_image_count; i++) {
        VkCommandBufferBeginInfo begin_info = { .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };

        vkBeginCommandBuffer(command_buffers[i], &begin_info);

        VkClearValue clear = { .color = { { 1.0f, 0.0f, 0.0f, 1.0f } } };  // Red

        VkRenderPassBeginInfo rp_begin = { .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
                                           .renderPass = render_pass,
                                           .framebuffer = framebuffers[i],
                                           .renderArea.offset = {0, 0},
                                           .renderArea.extent = {WIDTH, HEIGHT},
                                           .clearValueCount = 1,
                                           .pClearValues = &clear };

        vkCmdBeginRenderPass(command_buffers[i], &rp_begin, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdEndRenderPass(command_buffers[i]);

        vkEndCommandBuffer(command_buffers[i]);
    }
}

void create_sync_objects() {
    VkSemaphoreCreateInfo sem_info = { .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };
    VkFenceCreateInfo fence_info = { .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
                                     .flags = VK_FENCE_CREATE_SIGNALED_BIT };

    vkCreateSemaphore(device, &sem_info, NULL, &image_available_semaphore);
    vkCreateSemaphore(device, &sem_info, NULL, &render_finished_semaphore);
    vkCreateFence(device, &fence_info, NULL, &fence);
}

void draw_frame() {
    vkWaitForFences(device, 1, &fence, VK_TRUE, UINT64_MAX);
    vkResetFences(device, 1, &fence);

    uint32_t image_index;
    vkAcquireNextImageKHR(device, swapchain, UINT64_MAX, image_available_semaphore, VK_NULL_HANDLE, &image_index);
    VkPipelineStageFlags wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    VkSubmitInfo submit = { .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
                            .waitSemaphoreCount = 1,
                            .pWaitSemaphores = &image_available_semaphore,
                            .pWaitDstStageMask = &wait_stage,           // ← THIS WAS MISSING!
                            .signalSemaphoreCount = 1,
                            .pSignalSemaphores = &render_finished_semaphore,
                            .commandBufferCount = 1,
                            .pCommandBuffers = &command_buffers[image_index]
    };

    vkQueueSubmit(queue, 1, &submit, fence); // getting Segmentation fault in this line otherwise window is shown
    //
    VkPresentInfoKHR present = { .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
                                 .waitSemaphoreCount = 1,
                                 .pWaitSemaphores = &render_finished_semaphore,
                                 .swapchainCount = 1,
                                 .pSwapchains = &swapchain,
                                 .pImageIndices = &image_index };

    vkQueuePresentKHR(queue, &present);
}

int main() {
    create_xcb_window();
    create_instance();
    create_surface();
    pick_physical_device();
    create_logical_device();
    create_swapchain();
    create_image_views_and_framebuffers();
    create_command_buffers();
    create_sync_objects();

    while (1) {
        xcb_generic_event_t *event;
        while ((event = xcb_poll_for_event(connection))) {
            // if (event->response_type == XCB_DESTROY_NOTIFY) goto cleanup;
            free(event);
        }
        draw_frame();
    }
//
// cleanup:
//     vkDeviceWaitIdle(device);
//
//     vkDestroySemaphore(device, image_available_semaphore, NULL);
//     vkDestroySemaphore(device, render_finished_semaphore, NULL);
//     vkDestroyFence(device, fence, NULL);
//
//     for (uint32_t i = 0; i < swapchain_image_count; i++) {
//         vkDestroyFramebuffer(device, framebuffers[i], NULL);
//         vkDestroyImageView(device, image_views[i], NULL);
//     }
//     vkDestroyRenderPass(device, render_pass, NULL);
//     vkDestroyCommandPool(device, command_pool, NULL);
//     vkDestroySwapchainKHR(device, swapchain, NULL);
//     vkDestroyDevice(device, NULL);
//     vkDestroySurfaceKHR(instance, surface, NULL);
//     vkDestroyInstance(instance, NULL);
//
//     xcb_destroy_window(connection, window);
//     xcb_disconnect(connection);
//
//     return 0;
}
