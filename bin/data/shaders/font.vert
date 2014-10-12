#version 330 core

attribute vec2 vertexPosition;
attribute vec4 vertexColor;
attribute vec2 vertexUV;

uniform mat4 orthoMatrix;

out vec2 outUV;
out vec4 outColor;

// Simple vertex shader
void main(void)
{
	gl_Position = orthoMatrix * vec4(vertexPosition, 1, 1);

	outColor = vertexColor;
	outUV = vertexUV;
}