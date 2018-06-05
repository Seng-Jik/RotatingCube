#include "stdafx.h"
#include "StageSelectGUI.h"


using namespace Engine;

Game::Title::StageSelectGUI::StageSelectGUI(Title& t) :
	back_ { NewObject<Button>("back") }
{
	back_.Alpha() = 0;
	back_.Alpha().Run(1, 0.5f, 1);
	back_.Zoom() = 0.5f;
	back_.PosY() = -200;
	back_.PosX() = -100;
	back_.PosX().Run(-300, 0.5f, 2);

	tl_.AddTask([this] {
		back_.SetEnable(true);
	}, 0.6F);

	back_.SetOnClick([this,&t] {
		back_.Alpha().Run(0, 0.5f, 1);
		back_.PosX().Run(-100, 0.5f, 2);
		tl_.AddTask([this] { Kill(); },0.5f);

		t.ReturnToLogo();
	});
}

void Game::Title::StageSelectGUI::Update(float time)
{
	tl_.Update(time);
	Engine::ObjectSet<Engine::GameObject>::Update(time);
}
