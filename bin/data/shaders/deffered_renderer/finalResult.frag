#version 330 core

uniform sampler2D diffuseTexture; 
uniform sampler2D positionTexture;
uniform sampler2D normalTexture;

in vec2 vUV;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec4 color;

// Simple fragment shader
void main(void)
{	
	// 	base color of texture
	color = texture2D(diffuseTexture, vUV);
	mat4 pv = projectionMatrix * viewMatrix;

	vec3 vecPosition = texture2D(positionTexture, vUV).xyz;
	float power = 3.0f;	
	vec3 lightColor = vec3(0.2,0.5,0.2);
	vec3 lightPosition = (pv * vec4(0,5,0,1)).xyz;

	float mp = clamp(1-distance(lightPosition, vecPosition) / 20, 0, 1);

	color += vec4(lightColor * (power * mp), 1);
	color /= 2;

	lightColor = vec3(0.5,0.2,0);
	lightPosition = (pv * vec4(10,5,30,1)).xyz;

	mp = clamp(1-distance(lightPosition, vecPosition) / 20, 0, 1);

	color = (color + (texture2D(diffuseTexture, vUV)+vec4(lightColor * (power * mp), 1))/2)/2;	
}