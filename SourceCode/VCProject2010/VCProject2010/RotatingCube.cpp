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

	std::fill(deltas_.begin(), deltas_.end(), DirectX::XMFLOAT2(0, 0));

	model_.LightPower().Run(100, 1, 1);
}

void Game::GamePlay::RotatingCube::Update(float d)
{
	Engine::ObjectSet<Engine::Rendering::ObjModel>::Update(d);

	force_.Update(d);

	rotating_ += DirectX::XMFLOAT3(force_);
	model_.SetRotating(rotating_);

	const auto mouseState = std::get<0>(Engine::GetDevice().Mouse());
	const auto mouseDelta = Engine::GetDevice().MouseDelta();

	constexpr auto RotateScaling = 10;

	if (mouseState == MouseState::Down)
	{
		force_.Stop();
		force_ = DirectX::XMFLOAT3(0, 0, 0);
		rotating_.y += -mouseDelta.x * RotateScaling;
		rotating_.x += mouseDelta.y * RotateScaling;

		deltas_.Write(mouseDelta * d);

		Log("Rot", rotating_.x, rotating_.y,rotating_.z);
	}
	else if (mouseState == MouseState::JustDown)
	{
		model_.Alpha().Run(0.25f, 0.15f, 1);
	}
	else if (mouseState == MouseState::JustUp)
	{
		model_.Alpha().Run(1, 0.15f, 1);
		constexpr auto ForceScaling = 0.1f;
		const auto delta = std::accumulate(deltas_.begin(), deltas_.end(), DirectX::XMFLOAT2(0,0),
			[](DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b) {
			return LengthSqrt(a) > LengthSqrt(b) ? a : b;
		}) * (1 / max(d,0.01f)) * ForceScaling;

		std::fill(deltas_.begin(), deltas_.end(), DirectX::XMFLOAT2(0, 0));

		force_ = DirectX::XMFLOAT3
		(
			delta.y * RotateScaling,
			-delta.x * RotateScaling,
			0.0f
		);

		force_.Run(DirectX::XMFLOAT3(0, 0, 0),Clamp(LengthSqrt(force_) * 1000,0.0f,1.0f), 1);
	}
}

void Game::GamePlay::RotatingCube::FadeOut()
{
	model_.LightPower().Run(0, 0.25f, 1);
}
