#include "stdafx.h"
#include "DemoRotatingCube.h"

Game::EngineTests::DemoRotatingCube::DemoRotatingCube():
	cube_ { NewObject<DemoCube>() },
	x_ { 0 },
	y_ { 0 },
	z_ { 0 }
{
}

void Game::EngineTests::DemoRotatingCube::Update(float deltaTime)
{
	Engine::ObjectSet<DemoCube>::Update(deltaTime);

	x_ += deltaTime;
	y_ += deltaTime / 4;
	z_ += deltaTime / 8;
	cube_.SetRotation(x_, y_, 0);
}
