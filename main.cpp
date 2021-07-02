#include "engine/Engine.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#include "gameCode/main.h"

int main()
{
	Engine engine;
	Scene scene("res/scene.xml");

	Engine::start(&engine, &scene);

	while (!glfwWindowShouldClose(engine.getWindow()))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		engine.frame();
		Engine::tick();

		glfwSwapBuffers(engine.getWindow());
	}
}