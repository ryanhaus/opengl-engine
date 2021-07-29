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
in vec2 tCoord;

uniform vec3 viewPos;
uniform vec3 objectColor;
uniform LightArray lights;
uniform sampler2D objectTexture;
uniform bool hasTexture;

out vec4 fragColor;

const float ambient = 0.1;
const float specStrength = 0.5;

vec3 getLightDir(Light light)
{
	return normalize(light.pos - fragPos);
}

vec3 diffuse(Light light)
{
	vec3 normal = normalize(normalDir);
	float diff = max(0.0, dot(normal, getLightDir(light)));

	return diff * light.color;
}

vec3 specular(Light light)
{
	vec3 viewDir = normalize(viewPos - fragPos);

	vec3 normal = normalize(normalDir);
	vec3 reflectDir = reflect(-getLightDir(light), normal);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
	return vec3(specStrength * spec);
}

float sigma(float x)
{
	return 1.0 / (1.0 + exp(-x));
}

void main(void)
{
	vec3 overallColor = vec3(0.0);
	float strength = 0.0;

	for (int i = 0; i < lights.count; i++)
	{
		vec3 color = vec3(1.0);
		color *= diffuse(lights.lights[i]);
		color += specular(lights.lights[i]);
		overallColor += color;

		strength += lights.lights[i].intensity;
	}

	vec4 texColor = texture(objectTexture, tCoord);
	vec3 oCol = mix(objectColor, texColor.xyz, texColor.w);

	overallColor = mix(oCol, overallColor, sigma(strength) * .5);

	fragColor = vec4(overallColor + vec3(ambient), 1.0);
}