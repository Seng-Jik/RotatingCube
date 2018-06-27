#include "stdafx.h"
#include "Help.h"
#include "StageSelectGUI.h"

Game::Title::Help::Help(MainBackground& t) :
	back_{ NewObject<Engine::Button>("back") },
	helpHint_{ NewObject<Engine::Rendering::Sprite2D>("helpcontent") },
	board_{ NewObject<Engine::Rendering::ObjModel>("board") }
{
	back_.Alpha() = 0;
	back_.PosY() = -200;
	back_.PosX() = -100;
	back_.Zoom() = 0.5f;

	board_.SetCenterOffset(0, 0, -50);
	board_.SetScale(19.5F);
	board_.LightPower().Run(100, 1, 1);
	board_.Alpha() = 0;
	board_.Alpha().Run(1, 1, 1);

	tl_.AddTask([this] {
		back_.Alpha().Run(1, 0.5f, 1);
		back_.PosX().Run(-300, 0.5f, 2);
	}, 0.6F);

	tl_.AddTask([this] {
		back_.SetEnable(true);
		helpHintAlpha_.Run(1, 0.5f, 1);
	},1.2F);


	back_.SetOnClick([this, &t] {
		back_.Alpha().Run(0, 0.5f, 1);
		back_.PosX().Run(-100, 0.5f, 2);

		helpHintAlpha_.Run(0, 0.5f, 1);

		board_.LightPower().Run(0, 0.5f, 1);
		board_.Alpha().Run(0, 1, 1);

		tl_.AddTask([this, &t] {
			tl_.AddTask([this] { Kill(); }, 0.5f);
			t.ReturnToStageSelect();

			t.NewObject<Title::StageSelectGUI>(t);
		},0.5f);
	});

	helpHintAlpha_ = 0;
	helpHint_.SetZoom(0.5f);
	helpHint_.SetPos(0, -100);
}

void Game::Title::Help::Update(float d)
{
	helpHintAlpha_.Update(d);
	helpHint_.SetAlpha(helpHintAlpha_);
	Engine::ObjectSet<Engine::GameObject>::Update(d);
	tl_.Update(d);
}
