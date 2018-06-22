#include "stdafx.h"
#include "Help.h"
#include "StageSelectGUI.h"

Game::Title::Help::Help(MainBackground& t) :
	back_ { NewObject<Engine::Button>("back") }
{
	back_.Alpha() = 0;
	back_.PosY() = -200;
	back_.PosX() = -100;
	back_.Zoom() = 0.5f;

	tl_.AddTask([this] {
		back_.Alpha().Run(1, 0.5f, 1);
		back_.PosX().Run(-300, 0.5f, 2);
	}, 0.6F);

	tl_.AddTask([this] {
		back_.SetEnable(true);
	},1.2F);


	back_.SetOnClick([this, &t] {
		back_.Alpha().Run(0, 0.5f, 1);
		back_.PosX().Run(-100, 0.5f, 2);

		tl_.AddTask([this, &t] {
			tl_.AddTask([this] { Kill(); }, 0.5f);
			t.ReturnToStageSelect();

			t.NewObject<Title::StageSelectGUI>(t);
		},0.5f);
	});
}

void Game::Title::Help::Update(float d)
{
	Engine::ObjectSet<Engine::GameObject>::Update(d);
	tl_.Update(d);
}
