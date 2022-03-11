#version 330 core
layout (location = 0) in vec3 i_pos;
layout (location = 1) in vec2 i_coords;

out vec2 i_texCoords;

uniform mat4 u_model;
uniform mat4 u_projection;

void main() {
	gl_Position = u_projection * u_model * vec4(i_pos, 1.0);
	i_texCoords = i_coords;
}