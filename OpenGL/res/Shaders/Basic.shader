#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
out vec4 vertexColor;

void main()
{
   gl_Position = position;
}
        
#shader fragment
#version 330 core

out vec4 FragColor;
in vec4 vertexColor;

void main()
{
   FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}