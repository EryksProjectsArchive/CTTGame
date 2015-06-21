#version 330 core

uniform mat4 mvpMatrix;

attribute vec3 vertexPosition;

void main(void)
{
	gl_Position = mvpMatrix * vec4(vertexPosition, 1.0);
}