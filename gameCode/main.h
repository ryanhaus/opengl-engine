#pragma once

ShaderProgram* mainShader;
Model3D* monkey;

Engine* engine;
Scene* scene;

void Engine::start(Engine* e, Scene* s)
{
	engine = e;
	scene = s;

	mainShader = &scene->programMap["program"];
	mainShader->cameraEulerAngles.x = -M_PI / 2;
	mainShader->lightPosition = glm::vec3(-8.0f, 5.0f, 7.0f);

	monkey = &scene->modelMap["monkey"];
}

void Engine::tick()
{
	monkey->rotation.y += engine->getFrameTime() * 45.0;
	scene->draw(engine->getWindow());
}

void Engine::gl_callback(Callback callback)
{
	switch (callback)
	{
	case Callback::WinResize:
		break;
	}
}