#version 330 core
out vec4 FragColor;

in vec3 i_fragPos;
in vec3 i_normal;

struct StarLight  {

    vec3 ambient;
    vec3 diffuse;

    float constant;
    float linear;
    float quadratic;
};

uniform vec3 u_colour;
uniform StarLight u_star;

void main()
{
    vec3 normal = i_normal;

    vec3 lightDir = normalize(-i_fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    float distance = length(-i_fragPos);
    float attenuation = 1.0 / (u_star.constant + u_star.linear * distance + u_star.quadratic * ( distance * distance ));

    vec3 ambient = u_star.ambient * u_colour * attenuation;
    vec3 diffuse = u_star.diffuse * diff * u_colour * attenuation;

    FragColor = vec4(ambient+diffuse, 1.0f);
} 