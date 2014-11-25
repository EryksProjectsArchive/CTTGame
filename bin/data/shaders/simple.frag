#version 330 core

uniform sampler2D texture0; // Base texture from material.

in vec4 vColor;
in vec2 vUV;
in vec4 vPos;
in vec3 vNormal;


layout(location = 0) out vec3 diffuse;
layout(location = 1) out vec3 position;
layout(location = 2) out vec3 normal;
layout(location = 3) out float depth;

// Simple deffered fragment shader
void main(void)
{	
	diffuse = vColor.rgb * texture2D(texture0, vUV).rgb;
	position = vPos.xyz;
	normal = vNormal.xyz;
	depth = gl_FragCoord.z;
}