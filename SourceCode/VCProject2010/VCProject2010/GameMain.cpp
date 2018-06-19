#include "stdafx.h"
#include "GameMain.h"

Game::GamePlay::GameMain::GameMain(const decltype(*Stages)& stage):
	stageData_{ stage }
{
	NewObject<Engine::Rendering::ObjModel>(stage.ModelName);
}

void Game::GamePlay::GameMain::Draw() const
{
	Engine::ObjectSet<Engine::GameObject>::Draw();
}

void Game::GamePlay::GameMain::Update(float d)
{
	Engine::ObjectSet<Engine::GameObject>::Update(d);
}
