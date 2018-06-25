#include "stdafx.h"
#include "AnswerBoard.h"
#include "Sprite2D.h"

void Game::GamePlay::AnswerBoard::renderAnswerToRT(const decltype(*Stages)& stg)
{
	Engine::Rendering::ObjModel model{ stg.ModelName,false };
	model.SetCenterOffset
}

Game::GamePlay::AnswerBoard::AnswerBoard(const decltype(*Stages)&):
	board_ {
		NewObject<Engine::Rendering::ObjModel>("board", false)
	}
{
	board_.SetCenterOffset(0, 0, -50);
	board_.SetScale(19.5F);
	board_.LightPower().Run(100, 1, 1);

	std::tie(answer_, answerRtView_, std::ignore) = Engine::Rendering::CreateRTTTex();

	Engine::GetDevice().Context().OMSetRenderTargets(1, answerRtView_.GetAddressOf(), nullptr);
	const float col[] = { 0,0,0,0 };
	Engine::GetDevice().Context().ClearRenderTargetView(answerRtView_.Get(), col);
	Engine::GetDevice().ResetRenderTarget();

	auto& p = NewObject<Engine::Rendering::Sprite2D>(answer_);
	p.DrawOnTop = true;
}

void Game::GamePlay::AnswerBoard::FadeOut()
{
	board_.LightPower().Run(0, 0.25f, 1);
}
