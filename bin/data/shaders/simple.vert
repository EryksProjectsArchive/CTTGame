#version 330 core

// Engine uniforms.
uniform sampler2D texture0; // Base texture from material.
uniform mat4 modelMatrix; // Model matrix.
uniform mat4 projectionMatrix; // Projection matrix.
uniform mat4 viewMatrix; // View matrix.
uniform mat4 mvpMatrix; // MVP matrix.

attribute vec3 position;
attribute vec3 normal;

out vec3 fragNormal;

// Simple vertex shader
void main(void)
{
	fragNormal = normal;
	gl_Position = mvpMatrix * vec4(position, 1.0);
}