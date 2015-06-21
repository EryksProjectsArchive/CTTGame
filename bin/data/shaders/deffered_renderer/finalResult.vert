#version 330 core

uniform mat4 orthoMatrix;

attribute vec2 vertexPosition;
attribute vec2 vertexUV;
attribute vec4 vertexColor;

out vec2 vUV;

// Simple vertex shader
void main(void)
{
	gl_Position = orthoMatrix * vec4(vertexPosition, 0.0, 1.0);
	vUV = vertexUV;
}