#pragma once

ShaderProgram* mainShader;

Engine* engine;
Scene* scene;

void Engine::start(Engine* e, Scene* s)
{
	engine = e;
	scene = s;

	mainShader = &scene->programMap["program"];
	mainShader->cameraEulerAngles.x = -M_PI / 2;
}

void Engine::tick()
{
	mainShader->cameraPosition.x += mainShader->cameraPosition.x >= 2.0f ? -1.96f : 0.04f;
	mainShader->cameraEulerAngles.z += 0.01f;

	scene->draw();
}

void Engine::gl_callback(Callback callback)
{
	switch (callback)
	{
	case Callback::WinResize:
		break;
	}
}