#version 330 core

uniform sampler2D diffuseTexture; 
uniform sampler2D normalTexture;
uniform sampler2D depthTexture;

in vec2 vUV;

uniform mat4 unProjectMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 color;

// Day
vec3 ambientColor = vec3(0.9, 0.8, 0.7); 
// Night
//vec3 ambientColor = vec3(0.2, 0.2, 0.4);

vec3 specularColor = vec3(0.5,0.5,0.5);

vec3 getWorldPosition()
{
    float z = texture(depthTexture, vUV).r* 2.0 - 1.0;
    vec4 screenPosition = vec4(vUV * 2.0 - 1.0, z, 1.0);
    screenPosition = unProjectMatrix * screenPosition;

    return vec3(viewMatrix * vec4(screenPosition.xyz / screenPosition.w, 1));
}

vec4 calculatePointLight(vec3 position, vec3 normal, vec3 lightColor, vec3 lightPosition, float size, float power)
{	
	vec3 lightDirection = normalize(lightPosition - position);
	float multiplier = 0;
	float dir = dot(lightDirection, normal);
	if(dir >= -0.5)
	{
		multiplier = (1-clamp(distance(position, lightPosition)/size, 0, 1)) * (0.5+dir);
	}

	return vec4(lightColor * multiplier * power, 1);;
}

vec4 calculatePointLight_BlinnPhong(vec3 position, vec3 normal, vec3 lightColor, vec3 lightPosition, float size, float powe)
{
	vec3 lightDirection = normalize(lightPosition - position);
	float lambertian = max(dot(lightDirection, normal), 0.0);
	float specular = 0.0;

	if(lambertian > 0.0)
	{
		vec3 viewDirection = normalize(-position);
		vec3 halfDirection = normalize(lightDirection + viewDirection);
		float specularAngle = max(dot(halfDirection, normal), 0.0);
		specular = pow(specularAngle, 16.0);
	}

	float multiplier = (1-clamp(distance(position, lightPosition)/size, 0, 1));

	return vec4(ambientColor + (lambertian * lightColor + specular * specularColor)  * multiplier, 1);
}

void main(void)
{		
	vec4 lighting;

	// Base color of texture
	color = texture2D(diffuseTexture, vUV);

	// Get world position from depth buffer
	vec3 vecPosition = getWorldPosition();
	vec3 vecNormal = texture2D(normalTexture, vUV).xyz;

	// Light
	float power = 2.0f;
	float size = 20.0f;
	vec3 lightColor = vec3(1, 0.5, 0);
	vec3 lightPosition = vec3(viewMatrix * vec4(0.8,2,0.8,1));

	lighting += calculatePointLight_BlinnPhong(vecPosition, vecNormal, lightColor, lightPosition, size, power);

	color *= lighting;
}