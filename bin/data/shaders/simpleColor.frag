#version 330 core

uniform vec3 sunPos;
uniform vec3 sunLightColor;
uniform float sunLightPower;
uniform vec3 sunAmbientColor;
uniform sampler2D texture0; // Base texture from material.
out vec4 color;

in vec4 vColor;
in vec2 vUV;
in vec3 vPos;

in vec3 wsPos; // world space position
in vec3 csNormal; // camera space normal
in vec3 csEyeDir; // direction of camera eye - camera space
in vec3 csLightDir; // direction of light camera space

// Simple fragment shader
void main(void)
{
	vec3 matDiffuseColor = vec3(1,1,1);
	vec3 matAmbientColor = sunAmbientColor * matDiffuseColor;
	vec3 matSpecularColor = vec3(0.3,0.3,0.3);

	float distance = length(sunPos - wsPos);
	vec3 normalizedNormal = normalize(csNormal);
	vec3 noramlizedLightDir = normalize(csLightDir);

	float cosTheta = clamp(dot(normalizedNormal,noramlizedLightDir), 0, 1);

	vec3 eye = normalize(csEyeDir);
	vec3 reflect = reflect(-noramlizedLightDir, normalizedNormal);
	float cosAlpha = clamp(dot(eye, reflect), 0, 1);

	float powDistance = pow(distance, 2);

	color = vColor * vec4(matAmbientColor + matDiffuseColor * sunLightColor * sunLightPower * cosTheta / powDistance + matSpecularColor * sunLightColor * sunLightPower * pow(cosAlpha, 5) / powDistance, 1);
}