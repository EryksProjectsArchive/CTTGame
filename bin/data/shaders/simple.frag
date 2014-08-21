#version 330 core

// Engine uniforms.
uniform sampler2D texture0; // Base texture from material.
uniform mat4 modelMatrix; // Model matrix.
uniform mat4 projectionMatrix; // Projection matrix.
uniform mat4 viewMatrix; // View matrix.
uniform mat4 mvpMatrix; // Model*View*Projection matrix.

out vec4 color;

// Simple fragment shader
void main(void)
{
	color = vec4(0.0, 1.0, 0.0, 1.0);
}