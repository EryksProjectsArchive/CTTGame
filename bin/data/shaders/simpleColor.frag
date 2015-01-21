#version 330 core

in vec4 vColor;

layout(location = 0) out vec3 outDiffuse;
layout(location = 1) out vec3 outNormal;
layout(location = 2) out float outDepth;

// Simple fragment shader
void main(void)
{
	outDiffuse = vColor.rgb;
	outNormal = vec3(1,1,1);
	outDepth = gl_FragCoord.z;
}