#include "stdafx.h"
#include "StageComplete.h"
#include "Sprite2D.h"

Game::GamePlay::StageComplete::StageComplete()
{
	NewObject<Engine::Rendering::Sprite2D>("finish");
}

void Game::GamePlay::StageComplete::Update(float d)
{
	Engine::ObjectSet<>::Update(d);
}
