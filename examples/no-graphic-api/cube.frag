#version 460

layout(location = 0) in vec3 v_normal;
layout(location = 1) in vec4 v_color;
layout(location = 2) in vec3 v_world_pos;

layout(location = 0) out vec4 out_color;

void main() {
    vec3 N = normalize(v_normal);
    vec3 L = normalize(vec3(0.5, 0.8, 0.6)); // Key directional light
    vec3 L2 = normalize(vec3(-0.4, -0.2, -0.5)); // Soft fill light

    float diff1 = max(dot(N, L), 0.0);
    float diff2 = max(dot(N, L2), 0.0) * 0.3;
    float ambient = 0.25;

    float lighting = ambient + diff1 * 0.70 + diff2;
    vec3 shaded = v_color.rgb * lighting;

    out_color = vec4(shaded, 1.0);
}
