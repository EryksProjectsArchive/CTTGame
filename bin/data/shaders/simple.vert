#version 330 core

uniform mat4 mvpMatrix;
uniform vec3 sunPos;
uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

attribute vec3 vertexPosition;
attribute vec3 vertexNormal;
attribute vec2 vertexUV;
attribute vec4 vertexColor;

out vec2 vUV;
out vec3 vPos;
out vec4 vColor;

out vec3 wsPos; // world space position
out vec3 csNormal; // camera space normal
out vec3 csEyeDir; // direction of camera eye - camera space
out vec3 csLightDir; // direction of light camera space

// Simple vertex shader
void main(void)
{
	gl_Position = mvpMatrix * vec4(vertexPosition, 1.0);

	wsPos = (modelMatrix * vec4(vertexPosition, 1)).xyz;

	vec3 csVertexPos = (viewMatrix * modelMatrix * vec4(vertexPosition, 1)).xyz;
	csEyeDir = vec3(0,0,0) - csVertexPos;

	vec3 csLightPos = (viewMatrix * vec4(sunPos, 1)).xyz;
	csLightDir = csLightPos + csEyeDir;

	csNormal = (viewMatrix * modelMatrix * vec4(vertexNormal, 0)).xyz;

	vUV = vertexUV;
	vPos = vertexPosition;
	vColor = vertexColor;
}