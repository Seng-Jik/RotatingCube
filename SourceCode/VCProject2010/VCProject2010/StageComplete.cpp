#include "stdafx.h"
#include "StageComplete.h"
#include "Button.h"
#include "Clock.h"
#include "StageSelectGUI.h"
#include "MainBackground.h"

Game::GamePlay::StageComplete::StageComplete(float time,Engine::ObjectSet<>* mainBk, std::function<void()> gameMainExit):
	finishHint_{ NewObject<Engine::Rendering::Sprite2D>("finish") }
{
	hintProgress_.Run(1, 3, 1);

	auto& clk = NewObject<Clock>();
	clk.SetTime(time);
	clk.SetZoom(1);
	clk.Alpha() = 0;

	tl_.AddTask([&clk] {
		clk.Alpha().Run(1, 0.5f, 1);
	},3);

	auto& back = NewObject<Engine::Button>("list");
	auto& rest = NewObject<Engine::Button>("restart");
	auto& next = NewObject<Engine::Button>("next");

	back.PosX() = -100;
	next.PosX() = 100;

	back.PosY() = next.PosY() = rest.PosY() = -150;

	back.Alpha() = 0;
	rest.Alpha() = 0;
	next.Alpha() = 0;

	back.Zoom() = 0.95f;
	rest.Zoom() = 0.95f;
	next.Zoom() = 0.95f;

	tl_.AddTask([&] {

		tl_.AddTask([&back] {
			back.Zoom().Run(0.5f, 0.3f, 1);
			back.Alpha().Run(1, 0.3f, 1);
		}, 0.25f);

		tl_.AddTask([&rest] {
			rest.Zoom().Run(0.5f, 0.3f, 1);
			rest.Alpha().Run(1, 0.3f, 1);
		}, 0.45f);

		tl_.AddTask([&next] {
			next.Zoom().Run(0.5f, 0.3f, 1);
			next.Alpha().Run(1, 0.3f, 1);
		}, 0.65f);

		tl_.AddTask([&] {
			rest.SetEnable(true);
			back.SetEnable(true);
			next.SetEnable(true);
		},0.85f);
	},3.5f);

	const auto exitFunction = [&clk,&back,&rest,&next,gameMainExit,this] {
		hintProgress_.Run(0, 0.3f, 1);
		clk.Alpha().Run(0, 0.3f, 1);
		back.Alpha().Run(0, 0.3f, 1);
		rest.Alpha().Run(0, 0.3f, 1);
		next.Alpha().Run(0, 0.3f, 1);
		gameMainExit();
	};

	back.SetOnClick([exitFunction,mainBk,this] {
		exitFunction();
		static_cast<MainBackground*>(mainBk)->TaskList().AddTask([mainBk] {
			mainBk->NewObject<Title::StageSelectGUI>(static_cast<MainBackground&>(*mainBk));
		},0.75f);
		static_cast<MainBackground*>(mainBk)->ReturnToStageSelect();
	});

	rest.SetOnClick([exitFunction] {
		exitFunction();
	});

	next.SetOnClick([exitFunction] {
		exitFunction();
	});
}

void Game::GamePlay::StageComplete::Update(float d)
{
	tl_.Update(d);
	hintProgress_.Update(d);
	finishHint_.SetAlpha(hintProgress_);
	finishHint_.SetZoom(2 - 1.5f*hintProgress_);
	finishHint_.SetPos(0, 100 * hintProgress_);
	Engine::ObjectSet<>::Update(d);
}
