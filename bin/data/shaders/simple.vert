#version 330 core

uniform mat4 mvpMatrix;

attribute vec3 vertexPosition;
attribute vec3 vertexNormal;
attribute vec2 vertexUV;

out vec2 uv;

// Simple vertex shader
void main(void)
{
	gl_Position = mvpMatrix * vec4(vertexPosition, 1.0);

	uv = vertexUV;
}