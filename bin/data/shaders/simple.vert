#version 330 core

uniform mat4 mvpMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

attribute vec3 vertexPosition;
attribute vec3 vertexNormal;
attribute vec2 vertexUV;
attribute vec4 vertexColor;

out vec2 vUV;
out vec4 vPos;
out vec4 vColor;
out vec3 vNormal;

// Simple vertex shader
void main(void)
{
	gl_Position = mvpMatrix * vec4(vertexPosition, 1.0);

	vUV = vertexUV;
	vPos = gl_Position;
	vColor = vertexColor;
	vNormal = normalize(modelMatrix * viewMatrix * vec4(vertexNormal, 0)).xyz;
}