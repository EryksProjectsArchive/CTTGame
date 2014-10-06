#version 330 core

uniform sampler2D texture;

in vec4 outColor;
in vec2 outUV;

// Simple fragment shader
void main(void)
{
	gl_FragColor = outColor;
	gl_FragColor *= texture2D(texture, outUV);
}