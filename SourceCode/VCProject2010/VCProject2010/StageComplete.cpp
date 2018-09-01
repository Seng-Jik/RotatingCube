#include "stdafx.h"
#include "StageComplete.h"
#include "Button.h"
#include "Clock.h"
#include "StageSelectGUI.h"
#include "MainBackground.h"
#include "GameMain.h"
#include "SavaData.h"

Game::GamePlay::StageComplete::StageComplete(float time,StageName stg,StageName nextStg,Engine::ObjectSet<>* mainBk, std::function<void()> gameMainExit):
	finishHint_{ NewObject<Engine::Rendering::Sprite2D>("finish") }
{
	SaveData::Get().WriteTime(stg, time);
	SaveData::Get().OpenStage(nextStg);

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

	back.DisableActive();
	rest.DisableActive();
	next.DisableActive();

	tl_.AddTask([&,nextStg] {

		tl_.AddTask([&back] {
			back.Zoom().Run(0.5f, 0.3f, 1);
			back.Alpha().Run(1, 0.3f, 1);
		}, 0.25f);

		tl_.AddTask([&rest] {
			rest.Zoom().Run(0.5f, 0.3f, 1);
			rest.Alpha().Run(1, 0.3f, 1);
		}, 0.45f);

		tl_.AddTask([&next,nextStg] {
			next.Zoom().Run(0.5f, 0.3f, 1);
			next.Alpha().Run(nextStg == None ? 0.5f : 1, 0.3f, 1);
		}, 0.65f);

		tl_.AddTask([&, nextStg] {
			rest.EnableActive();
			back.EnableActive();
			if(nextStg != None)
				next.EnableActive();
			rest.SetEnable(true);
			back.SetEnable(true);
			next.SetEnable(nextStg != None);
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
		Mix_HaltMusic();
		exitFunction();
		static_cast<MainBackground*>(mainBk)->TaskList().AddTask([mainBk] {
			mainBk->NewObject<Title::StageSelectGUI>(static_cast<MainBackground&>(*mainBk));
		},0.75f);
		static_cast<MainBackground*>(mainBk)->ReturnToStageSelect();
	});

	rest.SetOnClick([exitFunction, mainBk, stg] {
		exitFunction();
		static_cast<MainBackground*>(mainBk)->TaskList().AddTask([mainBk,stg] {
			mainBk->NewObject<GameMain>(Stages[stg-1], static_cast<MainBackground*>(mainBk));
		}, 0.75f);
	});

	next.SetOnClick([exitFunction, nextStg , mainBk] {
		if (nextStg != None)
		{
			exitFunction();

			static_cast<MainBackground*>(mainBk)->TaskList().AddTask([mainBk, nextStg] {
				mainBk->NewObject<GameMain>(Stages[nextStg - 1], static_cast<MainBackground*>(mainBk));
			}, 0.75f);
		}
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
