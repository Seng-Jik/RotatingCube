#include "stdafx.h"
#include "AnswerBoard.h"

Game::GamePlay::AnswerBoard::AnswerBoard():
	board_ { NewObject<Engine::Rendering::ObjModel>("board",false) }
{
	board_.SetCenterOffset(0, 0, -50);
	board_.SetScale(19.5F);
	board_.LightPower().Run(100, 1, 1);
}
