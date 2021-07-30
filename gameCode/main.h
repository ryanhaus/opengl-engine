#pragma once
#include <cmath>

ShaderProgram* mainShader;

Engine* engine;
Scene* scene;
Camera* cam;

void Engine::start(Engine* e, Scene* s)
{
	engine = e;
	scene = s;
	cam = &scene->getCameras()[0];

	cam->setWindow(engine->getWindow());

	mainShader = scene->getProgram("program");

	glfwSetInputMode(engine->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Engine::tick()
{
	scene->getModel("mario1")->rotation.y -= engine->getFrameTime() * 90.0;
	scene->getModel("mario2")->rotation.y += engine->getFrameTime() * 90.0;

	glm::vec3 pointVec = MatrixGenerator::generatePointVector(cam->getRotation());
	float sens = 0.25;
	if (glfwGetKey(engine->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
		cam->setPosition(cam->getPosition() + pointVec * glm::vec3(sens));
	if (glfwGetKey(engine->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
		cam->setPosition(cam->getPosition() - pointVec * glm::vec3(sens));
	pointVec = MatrixGenerator::generatePointVector(glm::vec3(cam->getRotation().x + 90.0, 0.0, 0.0));
	if (glfwGetKey(engine->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
		cam->setPosition(cam->getPosition() + pointVec * glm::vec3(sens));
	if (glfwGetKey(engine->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
		cam->setPosition(cam->getPosition() - pointVec * glm::vec3(sens));

	scene->draw(engine->getWindow());
}

void Engine::gl_callback(Callback callback, int* params)
{
	switch (callback)
	{
	case Callback::WinResize:
		break;
	case Callback::MouseMove:
		float sens = 0.1f;
		float max_angle = 85.0f;

		glm::vec3 cr = cam->getRotation();
		cam->setRotation(glm::vec3(cr.x + params[0] * sens, std::max(std::min(cr.y -params[1] * sens, max_angle), -max_angle), 0.0));
		glfwSetCursorPos(engine->getWindow(), 0, 0);
		break;
	}
}