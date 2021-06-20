#version 430 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;

uniform mat4 mvp;

out vec3 normalDir;
out vec3 fragPos;

void main(void)
{
	normalDir = normal;
	fragPos = pos;

	gl_Position = mvp * vec4(pos, 1.0);
}
