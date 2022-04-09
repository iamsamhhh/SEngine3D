#version 330 core
out vec4 FragColor;
  
uniform vec3 color;
uniform vec3 lightColor;

void main()
{
    FragColor = vec4(color * lightColor, 1.0f);
}