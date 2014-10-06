#version 330 core

uniform mat4 mvpMatrix;

attribute vec3 vertexPosition;
attribute vec4 vertexColor;

out vec4 vColor;

// Simple vertex shader
void main(void)
{
	gl_Position = mvpMatrix * vec4(vertexPosition, 1.0);
	vColor = vertexColor;
}