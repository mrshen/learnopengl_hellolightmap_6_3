#version 330 core

in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;

	float ambientCoe;
	float shinness;
};
uniform Material objMaterial;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 camPos;


out vec4 FragColor;
void main()
{
	vec3 norm = normalize(normal);

	// diffuse color
	vec3 texDiffuse = texture(objMaterial.diffuse, texCoord).rgb;
	vec3 lightDir = normalize(lightPos - fragPos);
	vec3 diffuse = max(dot(lightDir, norm), 0.0) * texDiffuse * lightColor;

	// ambient color
	vec3 ambient = texDiffuse * vec3(objMaterial.ambientCoe) * lightColor * vec3(0.5);

	// specular color
	vec3 reflectDir = reflect(-lightDir, norm);
	vec3 viewDir = normalize(camPos - fragPos);
	float specCoe = max(dot(reflectDir, viewDir), 0.0);
	vec3 specular = pow(specCoe, objMaterial.shinness) * texture(objMaterial.specular, texCoord).rgb * lightColor;

	FragColor = vec4(ambient + diffuse + specular, 1.0);
}