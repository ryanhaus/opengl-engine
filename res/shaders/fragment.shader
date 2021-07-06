#version 430 core

const int LIGHT_MAX = 32;

struct Light
{
	vec3 pos;
	vec3 color;
	float intensity;
};

struct LightArray
{
	int count;
	Light lights[LIGHT_MAX];
};

in vec3 normalDir;
in vec3 fragPos;

uniform vec3 viewPos;
uniform vec3 objectColor;
uniform LightArray lights;

out vec4 fragColor;

const float ambient = 0.1;
const float specStrength = 0.5;

vec3 diffuse(Light light)
{
	vec3 normal = normalize(normalDir);
	vec3 lightDir = normalize(light.pos - fragPos);
	float diff = max(0.0, dot(normal, lightDir));

	return (diff * light.intensity) * light.color;
}

vec3 specular(Light light)
{
	vec3 viewDir = normalize(viewPos - fragPos);

	vec3 normal = normalize(normalDir);
	vec3 lightDir = normalize(light.pos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
	return vec3(specStrength * spec);
}

void main(void)
{
	vec3 overallColor = vec3(0.0);

	for (int i = 0; i < lights.count; i++)
	{
		vec3 color = objectColor;
		color *= diffuse(lights.lights[i]);
		color += specular(lights.lights[i]);
		overallColor += color;
	}

	fragColor = vec4(overallColor + vec3(ambient), 1.0);
}