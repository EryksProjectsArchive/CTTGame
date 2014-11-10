#version 330 core

uniform mat4 orthoMatrix;

attribute vec2 vertexPosition;
attribute vec4 vertexColor;
attribute vec2 vertexUV;

out vec4 vColor;

// Simple vertex shader
void main(void)
{
	gl_Position = orthoMatrix * vec4(vertexPosition, 1, 1);
	vColor = vertexColor;
}