
#version 330 core
layout (location = 0) in vec3 i_pos;

out vec3 i_fragPos;
out vec3 i_normal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    i_fragPos = vec3(u_model * vec4(i_pos, 1.0));
    i_normal = mat3(transpose(inverse(u_model))) * i_pos;
    gl_Position = u_projection * u_view * u_model * vec4(i_pos, 1.0);
} 