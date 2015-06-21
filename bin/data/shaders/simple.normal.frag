#version 330 core

uniform sampler2D diffuse;
uniform sampler2D normal;

in vec4 vColor;
in vec2 vUV;
in vec3 vNormal;

layout(location = 0) out vec3 outDiffuse;
layout(location = 1) out vec3 outNormal;
layout(location = 2) out float outDepth;

// Simple deffered fragment shader
void main(void)
{	
	outDiffuse = vColor.rgb * texture2D(diffuse, vUV).rgb;
	outNormal = vNormal * normalize(texture2D(normal, vUV).rgb * 2.0 - 1.0);
	outDepth = gl_FragCoord.z;
}