// Engine uniforms.
uniform sampler2D texture0; // Base texture from material.
uniform mat4 modelMatrix; // Model matrix.
uniform mat4 projectionMatrix; // Projection matrix.
uniform mat4 viewMatrix; // View matrix.
uniform mat4 mvpMatrix; // Model*View*Projection matrix.

in vec3 position;

// Simple vertex shader
void main(void)
{
	gl_Position = mvpMatrix * vec4(position, 1);
}