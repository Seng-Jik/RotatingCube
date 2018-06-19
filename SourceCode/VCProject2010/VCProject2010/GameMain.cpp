#include "stdafx.h"
#include "GameMain.h"

Game::GamePlay::GameMain::GameMain(const decltype(*Stages)& stage):
	rotCube_ { NewObject<RotatingCube>(stage) }
{
}
