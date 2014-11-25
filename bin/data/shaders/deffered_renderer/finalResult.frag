#version 330 core

uniform sampler2D diffuseTexture; 
uniform sampler2D normalTexture;
uniform sampler2D depthTexture;

in vec2 vUV;

uniform mat4 unProjectMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 color;

vec3 getWorldPosition()
{
    float z = texture(depthTexture, vUV).r* 2.0 - 1.0;
    vec4 screenPosition = vec4(vUV * 2.0 - 1.0, z, 1.0);
    screenPosition = unProjectMatrix * screenPosition;

    return (screenPosition.xyz / screenPosition.w);
}


// Simple fragment shader
void main(void)
{	
	// 	base color of texture
	color = texture2D(diffuseTexture, vUV);

	// Get world position from depth  buffer
	vec3 vecPosition = getWorldPosition();

	float power = 3.0f;	
	vec3 lightColor = vec3(0.2,0.5,0.2);
	vec3 lightPosition = vec3(0,5,0);

	float mp = clamp(1 - distance(lightPosition, vecPosition) / 20, 0, 1);

	color += vec4(lightColor * (power * mp), 1);
	color /= 2;

	lightColor = vec3(0.5,0.2,0);
	lightPosition = vec3(10,5,30);
	
	mp = clamp(1 - distance(lightPosition, vecPosition) / 20, 0, 1);

	color = (color + (texture2D(diffuseTexture, vUV)+vec4(lightColor * (power * mp), 1))/2)/2;	
}