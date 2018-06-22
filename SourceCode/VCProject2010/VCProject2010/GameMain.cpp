#include "stdafx.h"
#include "GameMain.h"
#include "StageSelectGUI.h"

Game::GamePlay::GameMain::GameMain(const decltype(*Stages)& stage,MainBackground* bk):
	clk_{ NewObject<Clock>() },
	back_ { NewObject<Engine::Button>("backs") }
{
	clk_.Alpha() = 0;
	clk_.Alpha().Run(1, 1, 1);
	clk_.SetPos(0, 0);
	clk_.SetPos(0, 200, 1);
	clk_.DrawOnTop = true;

	back_.Alpha() = 0;
	back_.Zoom() = 0.5f;
	back_.PosY() = -200;
	back_.PosX() = -100;
	back_.DrawOnTop = true;

	back_.SetOnClick([this,bk] {
		if (bk)
		{
			bk->ReturnToStageSelect();

			tasks_.AddTask([bk,this] {
				bk->NewObject<Title::StageSelectGUI>(*bk);
				Kill();
			},0.3f);
		}
		

		back_.SetEnable(false);
		Exit();
	});

	tasks_.AddTask([this,&stage] {
		rotCube_ = &NewObject<RotatingCube>(stage);
		ansBoard_ = &NewObject<AnswerBoard>();
		timer_ = 0;

		back_.Alpha().Run(0.5f, 0.5f, 1);
		back_.PosX().Run(-300, 0.5f, 2);
		tasks_.AddTask([this] {
			back_.SetEnable(true);
		}, 0.5f);
	}, 1);
}

void Game::GamePlay::GameMain::Update(float d)
{
	Engine::ObjectSet<Engine::GameObject>::Update(d);
	tasks_.Update(d);

	if(timer_ >= 0)
		timer_ += d;
	clk_.SetTime(timer_ >= 0 ? timer_ : 0);
}

void Game::GamePlay::GameMain::Exit()
{
	clk_.Alpha().Run(0, 0.25f, 1);
	ansBoard_->FadeOut();
	rotCube_->FadeOut();
	back_.Alpha().Run(0, 0.25f, 1);
}

