#version 460 core
in VS_OUT
{
    vec2 texcoord;
} fs_in;

uniform sampler2D tex0; // texture unit from C++

out vec4 FragColor; // final output

void main()
{
    FragColor = texture(tex0, fs_in.texcoord);
}
