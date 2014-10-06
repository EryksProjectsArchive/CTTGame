#version 330 core

uniform sampler2D texture0; // Base texture from material.
out vec4 color;

in vec4 vColor;
in vec2 vUV;
in vec3 vPos;

// Color from position
void main(void)
{
	color = vec4(vPos, 1);
}