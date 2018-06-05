#include "stdafx.h"
#include "StageSelectMenu.h"

Game::Title::StageSelectMenu::StageSelectMenu()
{
	Engine::Button* btns[6] = { nullptr };

	int num = 0;
	for (int y = 0; y <= 1; ++y)
	{
		for (int x = -1; x <= 1; ++x)
		{
			num++;

			std::string texName = "num" + std::to_string(num);
			auto& btn = NewObject<Engine::Button>(texName.c_str());

			btn.PosX() = x * 150.0f;
			btn.PosY() = y * -150.0f + 200.0f;

			btn.Zoom() = 0;

			btns[num - 1] = &btn;
		}
	}

	btnAniBatch[0].push_back(btns[0]);

	btnAniBatch[1].push_back(btns[1]);
	btnAniBatch[1].push_back(btns[3]);

	btnAniBatch[2].push_back(btns[2]);
	btnAniBatch[2].push_back(btns[4]);

	btnAniBatch[3].push_back(btns[5]);

	for (int i = 0;i < 4;++i)
	{
		tl_.AddTask([this,i] {
			for (auto p : btnAniBatch[i])
				p->Zoom().Run(0.5f, 0.15f, 1);
		}, i * 0.05f);
	}
}

void Game::Title::StageSelectMenu::Update(float time)
{
	Engine::ObjectSet<Engine::Button>::Update(time);
	tl_.Update(time);
}

void Game::Title::StageSelectMenu::ReturnToLogo()
{
	for (int i = 0; i < 4; ++i)
	{
		tl_.AddTask([this, i] {
			for (auto p : btnAniBatch[i])
				p->Zoom().Run(0, 0.15f, 1);
		}, i * 0.05f);
	}
}