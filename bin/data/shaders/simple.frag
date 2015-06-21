#version 330 core

uniform mat3 normalMatrix;
uniform sampler2D diffuse;

uniform uint mat_Parameters;

in vec4 vColor;
in vec2 vUV;
in vec3 vNormal;

layout(location = 0) out vec3 outDiffuse;
layout(location = 1) out vec3 outNormal;
layout(location = 2) out uint outParams;

// Simple deffered fragment shader
void main(void)
{	
	outDiffuse = vColor.rgb * texture2D(diffuse, vUV).rgb;
	outNormal = ((normalMatrix * vNormal) + 1) / 2;
	outParams = mat_Parameters;
}