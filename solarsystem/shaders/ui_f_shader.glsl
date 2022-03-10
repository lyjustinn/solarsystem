#version 330 core
out vec4 FragColor;

uniform vec3 u_colour;

void main()
{
    FragColor = vec4(u_colour, 1.0f);
} 