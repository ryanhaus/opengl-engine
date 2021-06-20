#version 330 core

in vec3 normalDir;
in vec3 fragPos;

out vec4 fragColor;

vec3 lightPos = vec3(-8.0f, 5.0f, 7.0f);
float ambient = 0.1;


void main(void)
{
	vec3 normal = normalize(normalDir);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(0.0, dot(normal, lightDir));

	vec3 color = vec3(1.0);
	color *= diff + ambient;


	fragColor = vec4(color, 1.0);
}