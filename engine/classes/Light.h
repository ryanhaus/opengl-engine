#pragma once
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

class Light
{
public:
	Light()
	{
		position = glm::vec3(0.0f);
		color = glm::vec3(1.0f);
		intensity = 1.0f;
	}

	void setPosition(glm::vec3 pos)
	{
		position = pos;
	}

	glm::vec3 getPosition()
	{
		return position;
	}

	void setColor(glm::vec3 col)
	{
		color = col;
	}

	glm::vec3 getColor()
	{
		return color;
	}

	void setIntensity(float in)
	{
		intensity = in;
	}

	float getIntensity()
	{
		return intensity;
	}

	void uniform(ShaderProgram* program, int i)
	{
		char lPosStr[64];
		char lColStr[64];
		char lIntStr[64];

		sprintf(lPosStr, "lights.lights[%i].pos", i);
		sprintf(lColStr, "lights.lights[%i].color", i);
		sprintf(lIntStr, "lights.lights[%i].intensity", i);

		glUniform3fv(program->getUniform(lPosStr), 1, &position[0]);
		glUniform3fv(program->getUniform(lColStr), 1, &color[0]);
		glUniform1f(program->getUniform(lIntStr), intensity);
	}
private:
	glm::vec3 position;
	glm::vec3 color;
	float intensity;
};