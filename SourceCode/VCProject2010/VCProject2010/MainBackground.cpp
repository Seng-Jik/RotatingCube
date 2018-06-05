#include "stdafx.h"
#include "MainBackground.h"
#include "Sprite2D.h"
#include "StageSelectGUI.h"

Game::MainBackground::MainBackground()	:
	pe_ { "TitleBackground" },
	pecbcpu_{ 0,DirectX::XMFLOAT2(0,0),Engine::GetDevice().GetScreenWdivH(),0 },
	pecb_{ Engine::Rendering::CreateConstantBuffer(pecbcpu_) }
{
	pe_.SetConstantBuffer(pecb_);
	light_ = 0;
	bkCamera_ = 1;
	bkCamera_.Run(0, 2.5F, 1);

	tl_.AddTask([this] {
		light_.Run(1.0F, 1, 1);
	}, 0.5f);

	tl_.AddTask([this] {
		reciveMouseClick_ = true;
	}, 2.5f);

	titleGUI_.Emplace(&NewObject<Title::TitleGUI>());
}


void Game::MainBackground::Draw() const
{
	Engine::Rendering::UpdateCBuffer(pecb_, pecbcpu_);
	pe_.Draw();

	Engine::ObjectSet<Engine::GameObject>::Draw();
}

void Game::MainBackground::Update(float time)
{
	Engine::ObjectSet<Engine::GameObject>::Update(time);
	pecbcpu_.iTime += time;
	light_.Update(time);
	bkCamera_.Update(time);
	pecbcpu_.iLight = light_;
	tl_.Update(time);

	pecbcpu_.iMouse = DirectX::XMFLOAT2(400 * bkCamera_, -64 * bkCamera_);

	if (std::get<0>(Engine::GetDevice().Mouse()) && reciveMouseClick_)
	{
		reciveMouseClick_ = false;
		Engine::ShowCursor(true);
		titleGUI_.Value()->Click();
		titleGUI_.Clear();
		bkCamera_.Run(1, 0.5f, 1);

		NewObject<Title::StageSelectGUI>(*this);
	}
}

void Game::MainBackground::ReturnToLogo()
{
	reciveMouseClick_ = false;
	Engine::ShowCursor(true);
	bkCamera_.Run(0, 2.5f, 1);

	titleGUI_.Emplace(&NewObject<Title::TitleGUI>());
	tl_.AddTask([this] {
		reciveMouseClick_ = true;
	}, 2.5f);
}

