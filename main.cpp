const float near_clip = 0.1f;
const float far_clip = 1000.0f;

#include "engine/Engine.h"
#include <cmath>

int main()
{
	Engine engine;

	ShaderProgram program;
	program.addShader("res/shaders/vertex.shader", GL_VERTEX_SHADER);
	program.addShader("res/shaders/fragment.shader", GL_FRAGMENT_SHADER);
	program.link();

	Model3D model("res/3d/square.stl");

	glClearColor(0.0, 1.0, 0.0, 1.0);

	program.cameraPosition = glm::vec3(0.0f, 2.0f, 5.0f);
	float x = 0.0f;

	while (!glfwWindowShouldClose(engine.getWindow()))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);

		program.cameraPosition.x = sinf(x += 0.03f) * 2.0f;

		model.draw(program);
	
		glfwSwapBuffers(engine.getWindow());
	}
}