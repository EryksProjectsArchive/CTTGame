#version 330 core

out vec4 color;

in vec4 vColor;

// Simple fragment shader
void main(void)
{
	color = vColor;
}