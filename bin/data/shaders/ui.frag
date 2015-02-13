#version 330 core

uniform sampler2D diffuse; 

out vec4 color;

in vec2 vUV;
in vec4 vColor;

// Simple fragment shader
void main(void)
{
	color = texture2D(diffuse, vUV)/* vColor*/;
}