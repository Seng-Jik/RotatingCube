#include "stdafx.h"
#include "RotatingCube.h"
#include "Math.h"

using namespace Engine::Math;

Game::GamePlay::RotatingCube::RotatingCube(const decltype(*Stages)& stage):
	model_{ NewObject<Engine::Rendering::ObjModel>(stage.ModelName) }
{
	model_.SetCenterOffset(stage.CenterOffset.x, stage.CenterOffset.y, stage.CenterOffset.z);
	rotating_ = stage.InitRotating;
	model_.SetScale(stage.Scaling);
}

void Game::GamePlay::RotatingCube::Update(float d)
{
	Engine::ObjectSet<Engine::Rendering::ObjModel>::Update(d);

	force_ *= 0.9f;

	rotating_ += DirectX::XMFLOAT3(force_);
	model_.SetRotating(rotating_);

	//Test
	if (std::get<0>(Engine::GetDevice().Mouse()) == Engine::MouseState::JustDown)
	{
		force_ = DirectX::XMFLOAT3(0.5F, 0.5F, 0);
	}
}
