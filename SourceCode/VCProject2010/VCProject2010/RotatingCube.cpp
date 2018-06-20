#include "stdafx.h"
#include "RotatingCube.h"
#include "Math.h"

using namespace Engine;
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

	force_.Update(d);

	rotating_ += DirectX::XMFLOAT3(force_);
	model_.SetRotating(rotating_);

	//Test
	/*if (std::get<0>(Engine::GetDevice().Mouse()) == Engine::MouseState::JustDown)
	{
		force_ = DirectX::XMFLOAT3(0.05F, 0.05F, 0);
		force_.Run(DirectX::XMFLOAT3(0, 0, 0), 1, 1);
	}*/

	const auto mouseState = std::get<0>(Engine::GetDevice().Mouse());
	const auto mouseDelta = Engine::GetDevice().MouseDelta();

	constexpr auto RotateScaling = 10;

	if (mouseState == MouseState::Down)
	{
		force_.Stop();
		rotating_.y += -mouseDelta.x * RotateScaling;
		rotating_.x += mouseDelta.y * RotateScaling;
	}
	else if (mouseState == MouseState::JustUp)
	{
		force_ = DirectX::XMFLOAT3
		(
			mouseDelta.x * RotateScaling,
			-mouseDelta.y * RotateScaling,
			0.0f
		);

		force_.Run(DirectX::XMFLOAT3(0, 0, 0),1 , 1);
	}
}
