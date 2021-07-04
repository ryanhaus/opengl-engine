#pragma once

ShaderProgram* mainShader;
Model3D* monkey;

Engine* engine;
Scene* scene;

void Engine::start(Engine* e, Scene* s)
{
	engine = e;
	scene = s;

	scene->getCameras()[0].setWindow(engine->getWindow());

	mainShader = scene->getProgram("program");
	monkey = scene->getModel("monkey");
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