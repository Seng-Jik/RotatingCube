#include "stdafx.h"
#include "Title.h"

Game::Title::Title::Title()	:
	pe_ { "TitleBackground" },
	pecbcpu_{ 0,DirectX::XMFLOAT2(0,0),Engine::GetDevice().GetScreenWdivH(),0 },
	pecb_{ Engine::Rendering::CreateConstantBuffer(pecbcpu_) }
{
	pe_.SetConstantBuffer(pecb_);
	light_ = 0;

	tl_.AddTask([this] {
		light_.Run(1.0F, 1, 1);
	}, 0.5f);
}


void Game::Title::Title::Draw() const
{
	Engine::Rendering::UpdateBuffer(pecb_, pecbcpu_);
	pe_.Draw();
}

void Game::Title::Title::Update(float time)
{
	pecbcpu_.iTime += time;
	light_.Update(time);
	pecbcpu_.iLight = light_;
	tl_.Update(time);
}

