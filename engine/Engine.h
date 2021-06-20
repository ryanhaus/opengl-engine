#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <cstdint>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "parsers/parserheader.h"
#include "classes/classheader.h"

class Engine
{
public:
	Engine()
	{
		glfwInit();
		window = glfwCreateWindow(720, 480, "Hello world", NULL, NULL);
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);
		
		glewInit();

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
	}

	~Engine()
	{
		glfwTerminate();
	}

	GLFWwindow* getWindow()
	{
		return window;
	}
private:
	GLFWwindow* window;
};