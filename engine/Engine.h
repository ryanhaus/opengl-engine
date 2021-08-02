#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>

#include "parsers/parserheader.h"
#include "classes/classheader.h"
#include "glCallbacks.h"

class Engine
{
public:
	Engine()
	{
		glfwInit();
		glfwWindowHint(GLFW_SAMPLES, 4);

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
		glfwSetCursorPosCallback(window, callback_mouseMove);

		prevSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		frameTime = 0;
	}

	~Engine()
	{
		glfwTerminate();
	}

	GLFWwindow* getWindow()
	{
		return window;
	}

	float getFrameTime()
	{
		return frameTime;
	}

	void frame()
	{
		int cSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		frameTime = (float)(cSeconds - prevSeconds) / 1000.0f;
		prevSeconds = cSeconds;
	}

	static void start(Engine* e, Scene* s);
	static void tick();
	static void gl_callback(Callback callback, int* params);
private:
	GLFWwindow* window;

	float frameTime;
	int prevSeconds;
};

void callback_winResize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);

	int* params = new int[2];
	params[0] = width;
	params[1] = height;

	Engine::gl_callback(Callback::WinResize, params);
}

void callback_mouseMove(GLFWwindow* window, double xpos, double ypos)
{
	int* params = new int[2];
	params[0] = floor(xpos);
	params[1] = floor(ypos);

	Engine::gl_callback(Callback::MouseMove, params);
}