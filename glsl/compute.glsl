#version 430 core
layout (local_size_x = 24, local_size_y = 24) in;
layout (rgba32f) uniform image2D data;

void main(void ) {
    ivec2 pos = ivec2(gl_GlobalInvocationID.xy);
    vec4 p = imageLoad(data, pos.xy);
    barrier();
    if (p.x > 0.8) return;
    imageStore( data,
                ivec2(gl_GlobalInvocationID.xy),
                vec4(p.x + 0.01, p.y + 0.01, 0, 1));
//                vec4(0, 0, 1.0, 1.0));
//                vec4((vec2(gl_GlobalInvocationID.xy) / vec2(gl_NumWorkGroups.xy)).xy, 0.0, 0.0));
}