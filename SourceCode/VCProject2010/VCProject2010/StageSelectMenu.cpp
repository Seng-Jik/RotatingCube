#include "stdafx.h"
#include "SavaData.h"
#include "StageSelectMenu.h"
#include "StageSelectGUI.h"
#include "GameMain.h"
#include "SoundEffect.h"
#include "Clock.h"
#include "StarDisplayer.h"

using namespace Game::GamePlay;

Game::Title::StageSelectMenu::StageSelectMenu(MainBackground& mainBackground, StageSelectGUI& gui)
{
	Engine::Button* btns[6] = { nullptr };

	int num = 0;
	for (int y = 0; y <= 1; ++y)
	{
		for (int x = -1; x <= 1; ++x)
		{
			num++;

			const auto stageOpened = Game::SaveData::Get().StageOpened(num);
			const auto stageTime = Game::SaveData::Get().GetStageTime(Game::GamePlay::StageName(num));
			std::string texName = stageOpened ? "num" + std::to_string(num) : "locked";
			auto& btn = NewObject<Engine::Button>(texName.c_str());
			
			

			btn.PosX() = x * 190.0f;
			btn.PosY() = y * -200.0f + 200.0f; 
			btn.SetColorMod(DirectX::XMFLOAT3(3,3,3));

			if (stageOpened && stageTime > 0)
			{
				auto& star = NewObject<StarDisplayer>(btn.PosX(), btn.PosY() -72.0f, stageTime, 0.25f);
				star.Show();

				auto& clock = NewObject<GamePlay::Clock>();
				clock.SetPos(btn.PosX(), btn.PosY() - 100);
				clock.Alpha() = 0;
				clock.Alpha().Run(1, 0.25f, 1);
				clock.SetZoom(0.5);
				clock.SetTime(stageTime);
				clock.Update(0);
				clock.SetColorMul(2);


			}

			btn.Zoom() = 0;

			btn.SetEnable(stageOpened);

			btns[num - 1] = &btn;

			if (stageOpened)
			{
				btn.SetOnClick([&mainBackground,this,&gui, num] {					
					tl_.AddTask([&mainBackground, this, &gui, num] {
						
						for (auto& p : btnAniBatch)
							for (auto i : p)
								i->DisableActive();
						gui.FadeOut();
						mainBackground.GoToGame();
						Exit();

						mainBackground.NewObject<Game::GamePlay::GameMain>(Game::GamePlay::Stages[num - 1],&mainBackground);
					},0.5f);
				});
			}
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
	Engine::ObjectSet<Engine::GameObject>::Update(time);
	tl_.Update(time);
}

void Game::Title::StageSelectMenu::Exit()
{
	for (int i = 0; i < 4; ++i)
	{
		tl_.AddTask([this, i] {
			for (auto p : btnAniBatch[i])
				p->Zoom().Run(0, 0.15f, 1);
		}, i * 0.05f);
	}

	for (auto& obj : *this)
	{
		try
		{
			dynamic_cast<Game::GamePlay::StarDisplayer&>(*obj).Hide();
		}
		catch (std::bad_cast)
		{

		}

		try
		{
			dynamic_cast<Game::GamePlay::Clock&>(*obj).Alpha().Run(0, 0.25f, 1);
		}
		catch (std::bad_cast)
		{

		}
	}

	tl_.AddTask([this] {
		Kill();
	}, 0.3f);
}
