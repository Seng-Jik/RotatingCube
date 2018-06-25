#include "stdafx.h"
#include "AnswerBoard.h"
#include "Sprite2D.h"


Game::GamePlay::AnswerBoard::AnswerBoard(const decltype(*Stages)& stg):
	board_ {
		NewObject<Engine::Rendering::ObjModel>("board", false)
	}
{
	board_.SetCenterOffset(0, 0, -50);
	board_.SetScale(19.5F);
	board_.LightPower().Run(100, 1, 1);

	auto& model = NewObject<Engine::Rendering::ObjModel>( stg.ModelName,false,"ModelBlack" );
	model.SetCenterOffset(stg.CenterOffset.x, stg.CenterOffset.y, stg.CenterOffset.z);
	model.SetRotating(stg.AnswerRotating);
	model.SetScale(stg.Scaling);
	model.DrawOnTop = true;
}

void Game::GamePlay::AnswerBoard::FadeOut()
{
	board_.LightPower().Run(0, 0.25f, 1);
}
