#include "stdafx.h"
#include "Title.h"

Game::Title::Title::Title()	:
	pe_ { "TitleBackground" },
	pecbcpu_{ 0,DirectX::XMFLOAT2(0,0),Engine::GetDevice().GetScreenWdivH() },
	pecb_{ Engine::Rendering::CreateConstantBuffer(pecbcpu_) }
{
	pe_.SetConstantBuffer(pecb_);
}


void Game::Title::Title::Draw() const
{
	Engine::Rendering::UpdateBuffer(pecb_, pecbcpu_);
	pe_.Draw();
}

void Game::Title::Title::Update(float time)
{
	pecbcpu_.iTime += time;
}
