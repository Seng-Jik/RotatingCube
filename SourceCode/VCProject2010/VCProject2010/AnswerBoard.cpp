#include "stdafx.h"
#include "AnswerBoard.h"

Game::GamePlay::AnswerBoard::AnswerBoard():
	board_ { NewObject<Engine::Rendering::ObjModel>("board",false) }
{
	board_.SetCenterOffset(0, 0, -50);
	board_.SetScale(19.5F);
	board_.LightPower().Run(100, 1, 1);
}

void Game::GamePlay::AnswerBoard::FadeOut()
{
	board_.LightPower().Run(0, 0.25f, 1);
}
