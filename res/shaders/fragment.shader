#version 330 core

in vec3 normalDir;
in vec3 fragPos;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 objectColor;

out vec4 fragColor;

const float ambient = 0.1;
const float specStrength = 0.5;


vec3 diffuse()
{
	vec3 normal = normalize(normalDir);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(0.0, dot(normal, lightDir));

	vec3 color = vec3(1.0);
	color *= diff;

	return color;
}

vec3 specular()
{
	vec3 viewDir = normalize(viewPos - fragPos);

	vec3 normal = normalize(normalDir);
	vec3 lightDir = normalize(lightPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
	return vec3(specStrength * spec);
}

void main(void)
{
	vec3 color = objectColor;
	color *= diffuse() + vec3(ambient);
	color += specular();

	fragColor = vec4(color, 1.0);
}