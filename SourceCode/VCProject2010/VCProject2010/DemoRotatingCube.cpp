#include "stdafx.h"
#include "DemoRotatingCube.h"
#include "Device.h"

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

	if (std::get<0>(Engine::GetDevice().Mouse()) == Engine::MouseState::Down)
	{
		x_ = std::get<1>(Engine::GetDevice().Mouse()).x;
		y_ = std::get<1>(Engine::GetDevice().Mouse()).y;
	}
	z_ += deltaTime / 8;
	cube_.SetRotation(x_,y_,z_);
}
