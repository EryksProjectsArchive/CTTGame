#version 330 core

uniform sampler2D texture;

int vec4 outColor;
int vec2 outUV;

out vec4 color;

// Simple fragment shader
void main(void)
{
	color = outColor * texture2D(texture, outUV);
}