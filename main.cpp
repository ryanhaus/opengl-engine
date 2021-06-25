const float near_clip = 0.1f;
const float far_clip = 1000.0f;

#include "engine/Engine.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

int main()
{
	Engine engine;
	Scene scene("res/scene.xml");

	ShaderProgram* mainShader = &scene.programMap["program"];
	mainShader->cameraEulerAngles.x = -M_PI / 2;

	while (!glfwWindowShouldClose(engine.getWindow()))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);

		mainShader->cameraPosition.x += mainShader->cameraPosition.x >= 2.0f ? -1.96f : 0.04f;
		scene.draw();

		glfwSwapBuffers(engine.getWindow());
	}
}