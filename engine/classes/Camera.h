#pragma once

class Camera
{
public:
	Camera(GLFWwindow* win = nullptr)
	{
		window = win;
		position = glm::vec3(0.0f);
		rotation = glm::vec3(0.0f);
	}

	void setPosition(glm::vec3 pos)
	{
		position = pos;
	}

	glm::vec3 getPosition()
	{
		return position;
	}

	void setRotation(glm::vec3 rot)
	{
		rotation = rot;
	}
	
	glm::vec3 getRotation()
	{
		return rotation;
	}

	void setWindow(GLFWwindow* win)
	{
		window = win;
	}

	GLFWwindow* getWindow()
	{
		return window;
	}
private:
	GLFWwindow* window;
	glm::vec3 position;
	glm::vec3 rotation;
};