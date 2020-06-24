#version 330 core
in vec2 tex_uv_out;

out vec4 FragColor;
uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, tex_uv_out);
} 