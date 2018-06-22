#include "stdafx.h"
#include "GameMain.h"

Game::GamePlay::GameMain::GameMain(const decltype(*Stages)& stage):
	clk_{ NewObject<Clock>() }
{
	clk_.Alpha() = 0;
	clk_.Alpha().Run(1, 1, 1);
	clk_.SetPos(0, 0);
	clk_.SetPos(0, 200, 1);

	tasks_.AddTask([this,&stage] {
		rotCube_ = &NewObject<RotatingCube>(stage);

		timer_ = 0;
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

