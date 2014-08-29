#version 330 core

uniform float scale;
uniform mat4 mvp;

attribute vec3 position;
attribute vec3 normal;

// Simple vertex shader
void main(void)
{
	vec3 pos = vec3(position.x * scale, position.y * scale, 0);
	gl_Position = vec4(pos, 1);
}