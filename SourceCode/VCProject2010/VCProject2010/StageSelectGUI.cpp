#include "stdafx.h"
#include "StageSelectGUI.h"


using namespace Engine;

Game::Title::StageSelectGUI::StageSelectGUI() :
	back_ { NewObject<Button>("back") }
{
	back_.Alpha() = 0;
	back_.Alpha().Run(1, 0.5f, 1);
	back_.Zoom() = 0.5f;
	back_.PosY() = -200;
	back_.PosX() = -100;
	back_.PosX().Run(-300, 0.5f, 2);
}
