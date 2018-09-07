#include "stdafx.h"
#include "StarDisplayer.h"

using namespace Engine;
using namespace Engine::Rendering;

Game::GamePlay::StarDisplayer::StarDisplayer()
{
}

void Game::GamePlay::StarDisplayer::Update(float t)
{
	ObjectSet<Sprite2D>::Update(t);
}
