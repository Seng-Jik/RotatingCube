#include "stdafx.h"
#include "StageSelectGUI.h"
#include "Help.h"

using namespace Engine;

Game::Title::StageSelectGUI::StageSelectGUI(MainBackground& t) :
	back_ { NewObject<Button>("back") },
	menu_ { NewObject<StageSelectMenu>(t,*this) },
	help_ { NewObject<Button>("help") }
{
	back_.Alpha() = 0;
	back_.Alpha().Run(1, 0.5f, 1);
	back_.Zoom() = 0.5f;
	back_.PosY() = -200;
	back_.PosX() = -100;
	back_.PosX().Run(-300, 0.5f, 2);

	help_.Alpha() = 0;
	help_.Alpha().Run(1, 0.5f, 1);
	help_.Zoom() = 0.5f;
	help_.PosY() = -200;
	help_.PosX() = 100;
	help_.PosX().Run(300, 0.5f, 2);

	tl_.AddTask([this] {
		back_.SetEnable(true);
		help_.SetEnable(true);
	}, 0.6F);

	back_.SetOnClick([this,&t] {
		back_.Alpha().Run(0, 0.5f, 1);
		back_.PosX().Run(-100, 0.5f, 2);

		help_.Alpha().Run(0, 0.5f, 1);
		help_.PosX().Run(100, 0.5f, 2);

		tl_.AddTask([this] { Kill(); },0.5f);

		t.ReturnToLogo();
		menu_.Exit();
	});

	help_.SetOnClick([this, &t] {
		back_.Alpha().Run(0, 0.5f, 1);
		back_.PosX().Run(-100, 0.5f, 2);

		help_.Alpha().Run(0, 0.5f, 1);
		help_.PosX().Run(100, 0.5f, 2);
	   
		tl_.AddTask([this] { Kill(); }, 0.5f);

		t.NewObject<Help>(t);

		t.GoToHelp();
		menu_.Exit();
	});
}

void Game::Title::StageSelectGUI::Update(float time)
{
	tl_.Update(time);
	Engine::ObjectSet<Engine::GameObject>::Update(time);
}

void Game::Title::StageSelectGUI::FadeOut()
{
	back_.Alpha().Run(0, 0.5f, 1);
	back_.PosX().Run(-100, 0.5f, 2);

	help_.Alpha().Run(0, 0.5f, 1);
	help_.PosX().Run(100, 0.5f, 2);

	tl_.AddTask([this] {
		Kill();
	}, 0.75F);
}
