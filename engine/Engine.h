#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <cstdint>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "parsers/parserheader.h"
#include "classes/classheader.h"


#include "glCallbacks.h"

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
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glfwSetFramebufferSizeCallback(window, callback_winResize);
	}

	~Engine()
	{
		glfwTerminate();
	}

	GLFWwindow* getWindow()
	{
		return window;
	}

	static void start(Engine* e, Scene* s);
	static void tick();
	static void gl_callback(Callback callback);
private:
	GLFWwindow* window;
};

void callback_winResize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	Engine::gl_callback(Callback::WinResize);
}