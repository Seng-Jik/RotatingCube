#include "stdafx.h"
#include "GameMain.h"

Game::GamePlay::GameMain::GameMain(const decltype(*Stages)& stage)
{
	tasks_.AddTask([this,&stage] {
		rotCube_ = &NewObject<RotatingCube>(stage);
	}, 1);
}

void Game::GamePlay::GameMain::Update(float d)
{
	Engine::ObjectSet<Engine::GameObject>::Update(d);
	tasks_.Update(d);
}

