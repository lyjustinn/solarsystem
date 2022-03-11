#version 330 core
in vec2 i_texCoords;
out vec4 FragColor;

uniform sampler2D u_glyph;
uniform vec3 u_colour;

void main() {
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_glyph, i_texCoords).r);
	FragColor = vec4(u_colour, 1.0) * sampled;
}