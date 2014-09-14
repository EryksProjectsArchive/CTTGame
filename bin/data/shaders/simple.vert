#version 330 core

uniform mat4 mvpMatrix;

attribute vec3 vertexPosition;
attribute vec3 vertexNormal;
attribute vec2 vertexUV;
attribute vec4 vertexColor;

out vec2 vUV;
out vec3 vPos;
out vec4 vColor;

// Simple vertex shader
void main(void)
{
	gl_Position = mvpMatrix * vec4(vertexPosition, 1.0);

	vUV = vertexUV;
	vPos = vertexPosition;
	vColor = vertexColor;//vec4(vertexColor.rgb, 1);
}