#version 330 core

attribute vec2 vertexPosition;
attribute vec4 vertexColor;
attribute vec2 vertexUV;

out vec2 outUV;
out vec2 outColor;

// Simple vertex shader
void main(void)
{
	gl_Position = vec4(vertexPosition, 0, 1);

	outColor = vertexColor;
	outUV = vertexUV;
}