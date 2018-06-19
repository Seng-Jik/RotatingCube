#include "stdafx.h"
#include "RotatingCube.h"

Game::GamePlay::RotatingCube::RotatingCube(const decltype(*Stages)& stage):
	model_{ NewObject<Engine::Rendering::ObjModel>(stage.ModelName) }
{
	model_.SetCenterOffset(stage.CenterOffset.x, stage.CenterOffset.y, stage.CenterOffset.z);
	model_.SetRotating(stage.InitRotating.x, stage.InitRotating.y, stage.InitRotating.z);
	model_.SetScale(stage.Scaling);
}

void Game::GamePlay::RotatingCube::Update(float d)
{
	Engine::ObjectSet<Engine::Rendering::ObjModel>::Update(d);
}
