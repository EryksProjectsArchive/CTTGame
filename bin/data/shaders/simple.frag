#version 330 core

uniform sampler2D texture0; // Base texture from material.
out vec4 color;

in vec4 vColor;
in vec2 vUV;
in vec3 vPos;

// Simple fragment shader
void main(void)
{
	color = vColor * texture2D(texture0, vUV);
}