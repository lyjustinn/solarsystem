#version 330 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in vec3 o_pos;

uniform sampler2D u_texture;

void main()
{
    //vec3 colour = texture(u_texture, o_pos).rgb;
    //FragColor = vec4(1.0f, 0.73f, 0.03f, 1.0f) * 2.0;
    vec2 coord = vec2(o_pos * 0.5 + vec3(0.5));
    FragColor = texture(u_texture, coord);

    BrightColor = vec4(FragColor.rgb, 1.0);
} 