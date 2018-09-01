#include "stdafx.h"
#include "GameMain.h"
#include "StageSelectGUI.h"
#include "StageComplete.h"

Mix_Music * Game::GamePlay::GameMain::bgm_ = nullptr;

void Game::GamePlay::GameMain::ClearMusic()
{
	Mix_FreeMusic(bgm_);
}

Game::GamePlay::GameMain::GameMain(const decltype(*Stages)& stage,MainBackground* bk):
	clk_{ NewObject<Clock>() },
	back_ { NewObject<Engine::Button>("back") }
{
	clk_.Alpha() = 0;
	clk_.Alpha().Run(1, 1, 1);
	clk_.SetPos(0, 0);
	clk_.SetPos(0, 200, 1);
	clk_.DrawOnTop = true;

	if(!bgm_)
		bgm_ = Mix_LoadMUS("GameBGM.ogg");

	back_.Alpha() = 0;
	back_.Zoom() = 0.5f;
	back_.PosY() = -200;
	back_.PosX() = -100;
	back_.DrawOnTop = true;

	back_.SetOnClick([this,bk] {
		Mix_HaltMusic();
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

	tasks_.AddTask([this,&stage,bk] {
		if(!Mix_PlayingMusic())
			Mix_PlayMusic(bgm_,-1);
		rotCube_ = &NewObject<RotatingCube>(stage);
		ansBoard_ = &NewObject<AnswerBoard>(stage);
		timer_ = 0;

		back_.Alpha().Run(0.5f, 0.5f, 1);
		back_.PosX().Run(-300, 0.5f, 2);
		tasks_.AddTask([this] {
			back_.SetEnable(true);
		}, 0.5f);

		rotCube_->SetFinishedEvent([bk,this, stage]() {
			back_.Alpha().Run(0, 0.25f, 1);
			tasks_.AddTask([this,bk, stage] {
				clk_.Alpha().Run(0, 0.25f, 1);
				NewObject<StageComplete>(clk_.GetTime(),stage.Current, stage.NextStage,bk, [this]() {Exit(); });
			},0.25f);
		});
	}, 1);
}

void Game::GamePlay::GameMain::Update(float d)
{
	Engine::ObjectSet<Engine::GameObject>::Update(d);
	tasks_.Update(d);


	if (rotCube_)
	{
		if (!rotCube_->Finished())
		{
			if (timer_ >= 0 && rotCube_->Started())
				timer_ += d;

			clk_.SetTime(timer_ >= 0 ? timer_ : 0);
		}
	}
}

void Game::GamePlay::GameMain::Exit()
{
	clk_.Alpha().Run(0, 0.25f, 1);
	ansBoard_->FadeOut();
	rotCube_->FadeOut();
	back_.Alpha().Run(0, 0.25f, 1);

	tasks_.AddTask([this] {
		Kill();
	}, 0.3f);
}

