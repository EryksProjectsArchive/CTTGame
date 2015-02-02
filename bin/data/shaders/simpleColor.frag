#version 330 core

in vec4 vColor;
uniform uint mat_Parameters;
layout(location = 0) out vec3 outDiffuse;
layout(location = 1) out vec3 outNormal;
layout(location = 2) out uint outParams;

// Simple fragment shader
void main(void)
{
	outDiffuse = vColor.rgb;
	outNormal = vec3(1,1,1);
	outParams = mat_Parameters;
}