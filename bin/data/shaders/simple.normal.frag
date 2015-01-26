#version 330 core

uniform mat3 normalMatrix;

uniform sampler2D diffuse;
uniform sampler2D normal;

in vec4 vColor;
in vec2 vUV;
in vec3 vNormal;

layout(location = 0) out vec3 outDiffuse;
layout(location = 1) out vec3 outNormal;

//Path: Deffered rendering
//Normal map simple
void main(void)
{	
	outDiffuse = vColor.rgb * texture2D(diffuse, vUV).rgb;
	
	vec3 normalMapNormal = (texture2D(normal, vUV).rgb * 2.0 - 1.0) * 0.1;

	vec3 finalNormal = (normalMatrix * (vNormal * normalMapNormal));

	outNormal = (finalNormal + 1) / 2;
}