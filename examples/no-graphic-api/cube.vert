#version 460
#extension GL_EXT_buffer_reference : require
#extension GL_EXT_scalar_block_layout : require
#extension GL_EXT_shader_explicit_arithmetic_types_int64 : require

//~ sa: Vertex structure pulled directly from 64-bit memory address
struct Vertex {
    vec3 pos;
    vec3 normal;
    vec4 color;
};

//~ sa: Direct 64-bit buffer reference for vertices (Manual Vertex Pulling)
layout(buffer_reference, scalar) readonly buffer VertexBuffer {
    Vertex vertices[];
};

//~ sa: Root Data struct - pointed to by single 64-bit root pointer
layout(buffer_reference, scalar) readonly buffer RootData {
    uint64_t vertices_ptr;
    mat4 mvp;
    mat4 model;
};

//~ sa: Root pointer delivered via push constants (replacing descriptor sets)
layout(push_constant) uniform PushConstant {
    uint64_t vertex_root_ptr;
    uint64_t pixel_root_ptr;
} pc;

layout(location = 0) out vec3 v_normal;
layout(location = 1) out vec4 v_color;
layout(location = 2) out vec3 v_world_pos;

void main() {
    // Dereference root pointer directly from 64-bit GPU virtual address
    RootData root = RootData(pc.vertex_root_ptr);

    // Pull vertex data directly from 64-bit buffer pointer
    VertexBuffer vb = VertexBuffer(root.vertices_ptr);
    Vertex v = vb.vertices[gl_VertexIndex];

    vec4 world_pos = root.model * vec4(v.pos, 1.0);
    gl_Position    = root.mvp * vec4(v.pos, 1.0);

    // Pass attributes to fragment stage
    v_normal    = mat3(root.model) * v.normal;
    v_color     = v.color;
    v_world_pos = world_pos.xyz;
}
