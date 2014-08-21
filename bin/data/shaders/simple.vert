#version 330 core

// Engine uniforms.
uniform sampler2D texture0; // Base texture from material.
uniform mat4 modelMatrix; // Model matrix.
uniform mat4 projectionMatrix; // Projection matrix.
uniform mat4 viewMatrix; // View matrix.
uniform mat4 mvpMatrix; // Model*View*Projection matrix.

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

// Simple vertex shader
void main(void)
{
	gl_Position = mvpMatrix * vec4(position, 1);
}