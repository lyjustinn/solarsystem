#version 330 core
out vec4 FragColor;

in vec2 o_texCoords;

uniform sampler2D u_scene;
uniform sampler2D u_bloomBlur;
uniform bool u_bloom;
uniform float u_exposure;

void main()
{             
    vec3 hdrColor = texture(u_scene, o_texCoords).rgb;

    // tone mapping
    vec3 result = vec3(1.0) - exp(-hdrColor * u_exposure);

    FragColor = vec4(result, 1.0);
}