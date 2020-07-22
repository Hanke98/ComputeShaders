#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 tex_uv;

out vec2 tex_uv_out;
void main()
{
    tex_uv_out = tex_uv;
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
}