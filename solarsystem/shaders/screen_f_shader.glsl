#version 330 core
out vec4 FragColor;

in vec2 o_texCoords;

uniform sampler2D u_scene;
uniform sampler2D u_bloomBlur;
uniform float u_exposure;

void main()
{             
    vec3 hdrColor = texture(u_scene, o_texCoords).rgb;

    vec3 bloomColor = texture(u_bloomBlur, o_texCoords).rgb;
    
    hdrColor += bloomColor; // additive blending    

    // tone mapping
    vec3 result = vec3(1.0) - exp(-hdrColor * u_exposure);

    //gamma correction
    result = pow(result, vec3(1.0 / 2.2));

    FragColor = vec4(result, 1.0);
}