#version 330 core

uniform sampler2D diffuseTexture; 
uniform sampler2D normalTexture;
uniform sampler2D depthTexture;
uniform sampler2D shadowTexture;
uniform usampler2D materialParameterTexture;

in vec2 vUV;

uniform mat4 unProjectMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 depthBiasMVP;

out vec4 color;

// Material parameters
const uint IS_SHADELESS = 1u;
const uint CAST_SHADOWS = 2u;
const uint RECEIVE_SHADOWS = 4u;

// Day
vec3 ambientColor = vec3(0.1, 0.1, 0.1);
vec3 specularColor = vec3(0.5, 0.5, 0.5);

vec3 getWorldPosition()
{
    float z = texture(depthTexture, vUV).r * 2.0 - 1.0;
    vec4 screenPosition = vec4(vUV * 2.0 - 1.0, z, 1.0);
    screenPosition = unProjectMatrix * screenPosition;
    return vec3(screenPosition / screenPosition.w);
}

/*bool isFlagSet(uint flags, uint flag)
{
	return bool((flags & flag) == flag);
}*/

vec2 shift[20] = vec2[20](
	vec2(0.427835603932, 0.477655295239),
	vec2(0.251234811205, -0.57155564682),
	vec2(0.660700865496, -0.690274124225),
	vec2(0.210817722507, 0.236357604372),
	vec2(0.408419298903, -0.60207668689),
	vec2(-0.843159634641, -0.908271879051),
	vec2(-0.405977503359, -0.258039204955),
	vec2(-0.113997265239, 0.309559575797),
	vec2(0.11578311972, 0.668418375007),
	vec2(-0.0348932234126, 0.581132158975),
	vec2(-0.394591224328, -0.971131362331),
	vec2(-0.0244046280709, -0.887950429262),
	vec2(-0.514683384993, -0.736217282451),
	vec2(0.0922579997571, -0.549640301737),
	vec2(0.602153194993, 0.950229230671),
	vec2(0.646078312638, 0.332015424308),
	vec2(0.293169534658, 0.457958499538),
	vec2(0.571889062031, -0.723372669044),
	vec2(0.32334337527, -0.698435936951),
	vec2(0.618576434245, 0.0463357570433)
);

vec4 calculatePointLight_BlinnPhong(uint materialParams, vec3 position, vec3 normal, vec3 lightColor, vec3 lightPosition, float size, float powe)
{
	float visibility = 1.0;

	// If our material receive shadows do calculation
	if((materialParams & RECEIVE_SHADOWS) == RECEIVE_SHADOWS)
	{
		vec3 wsPos = getWorldPosition();
		vec4 uv = depthBiasMVP * vec4(wsPos, 1);
		if(uv.x <= 1 && uv.y <= 1 && uv.x >= 0 && uv.y >= 0)
		{			
			for(int i = 0; i < 20; ++i)
			{
				float depthValue = texture(shadowTexture, uv.xy + shift[i]/(10 * 200)).r;
				if(depthValue < uv.z)
				{
	 				visibility -= (0.8 / 20);
 				}
			}
		}
	}
	// Convert light position to screen-space.	
	lightPosition = vec3(viewMatrix * vec4(lightPosition, 1));

	vec3 lightDirection = normalize(lightPosition - position);
	float lambertian = max(dot(lightDirection, normal), 0.0);
	float specular = 0.0;

	if(lambertian > 0.0)
	{
		vec3 viewDirection = normalize(-position);
		vec3 halfDirection = normalize(lightDirection + viewDirection);
		float shininess = 1.0f;
		float specularAngle = max(pow(dot(normal, halfDirection), shininess), 0.0);
		specular = pow(specularAngle, 16.0);
	}

	float multiplier = 1.0-clamp(distance(position, lightPosition)/size, 0, 1);

	return vec4(ambientColor + ((lambertian * lightColor + specular * specularColor) * multiplier) * visibility, 1);
}

void main(void)
{		
	vec4 lighting = vec4(0, 0, 0, 0);

	// Base color of texture
	color = texture2D(diffuseTexture, vUV);

	// Get material parameters flags.
	uint parameters = texture(materialParameterTexture, vUV).x;

	// Check if we have to compute lights and shadows for this pixel
	if((parameters & IS_SHADELESS) != IS_SHADELESS)
	{
		// Get world position from depth buffer
		vec3 vecPosition = vec3(viewMatrix * vec4(getWorldPosition(), 1));
		vec3 vecNormal = normalize((texture2D(normalTexture, vUV).xyz * 2) - 1);

		// Sun
		float power = 10.0f;
		float size = 1000.0f;
		vec3 lightColor = vec3(1, 1, 1);
		vec3 lightPosition = vec3(200,500,0);

		lighting += calculatePointLight_BlinnPhong(parameters, vecPosition, vecNormal, lightColor, lightPosition, size, power);

		// Light
		power = 1.0f;
		size = 20.0f;
		lightColor = vec3(1, 0.5, 0);
		lightPosition = vec3(0.8,2,0.8);

		lighting += calculatePointLight_BlinnPhong(parameters, vecPosition, vecNormal, lightColor, lightPosition, size, power);

		color *= lighting;
	}
}