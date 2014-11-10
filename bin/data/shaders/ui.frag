#version 330 core

uniform sampler2D texture; 

out vec4 color;

in vec4 vColor;

// Simple fragment shader
void main(void)
{
	color = vColor;
}