#version 330 core

in vec2 uv;
uniform sampler2D texture0; // Base texture from material.
out vec4 color;

// Simple fragment shader
void main(void)
{
	color = vec4(texture2D(texture0, uv).rgb, 1);
}