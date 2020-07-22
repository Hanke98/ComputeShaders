#version 430 core
layout (local_size_x = 1024) in;

layout (rgba32f, binding=0) uniform imageBuffer velocity_buffer;
layout (rgba32f, binding=1) uniform imageBuffer position_buffer;

uniform float dt = 1.0;
void main() {
    vec4 vel = imageLoad(velocity_buffer, int(gl_GlobalInvocationID.x));
    vec4 pos = imageLoad(position_buffer, int(gl_GlobalInvocationID.x));

    pos.xyz += vel.xyz * dt;
    pos.w -= 0.0001 * dt;

    if (pos.w <= 0.0)
    {
        pos.xyz = -pos.xyz * 0.01;
        vel.xyz *= 0.01;
        pos.w += 1.0f;
    }

    imageStore(position_buffer, int(gl_GlobalInvocationID.x), pos); // 类似的还有 imageSize
    imageStore(velocity_buffer, int(gl_GlobalInvocationID.x), vel);
}