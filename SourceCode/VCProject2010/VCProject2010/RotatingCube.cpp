#include "stdafx.h"
#include "RotatingCube.h"
#include "Math.h"


using namespace Engine;
using namespace Engine::Math;

Game::GamePlay::RotatingCube::RotatingCube(const decltype(*Stages)& stage):
	model_{ NewObject<Engine::Rendering::ObjModel>(stage.ModelName) }
{
	answer_.x = fmodf(stage.AnswerRotating.x, 2*3.1415926f);
	answer_.y = fmodf(stage.AnswerRotating.y, 2*3.1415926f);
	answer_.z = 0;

	model_.SetCenterOffset(stage.CenterOffset.x, stage.CenterOffset.y, stage.CenterOffset.z);
	rotating_ = stage.InitRotating;
	model_.SetScale(stage.Scaling);

	std::fill(deltas_.begin(), deltas_.end(), DirectX::XMFLOAT2(0, 0));

	model_.LightPower().Run(100, 1, 1);
}

void Game::GamePlay::RotatingCube::Update(float d)
{
	Engine::ObjectSet<Engine::Rendering::ObjModel>::Update(d);

	rotating_.Update(d);
	force_.Update(d);

	

	rotating_.Value() += DirectX::XMFLOAT3(force_);

	rotating_.Value().x = fmodf(rotating_.Value().x, 2 * 3.1415926f);
	rotating_.Value().y = fmodf(rotating_.Value().y, 2 * 3.1415926f);

	rotating_.Value() += DirectX::XMFLOAT3(3.1415926f * 8, 3.1415926f * 8,0);

	rotating_.Value().x = fmodf(rotating_.Value().x, 2 * 3.1415926f);
	rotating_.Value().y = fmodf(rotating_.Value().y, 2 * 3.1415926f);

	model_.SetRotating(rotating_);

	const auto mouseState = std::get<0>(Engine::GetDevice().Mouse());
	const auto mouseDelta = Engine::GetDevice().MouseDelta();

	constexpr float KeyRotate = 0.0025f;
	if (Engine::GetDevice().KeyDown(VK_UP))
	{
		force_.Stop();
		force_ = DirectX::XMFLOAT3(0, 0, 0);

		rotating_.Value() += DirectX::XMFLOAT3(KeyRotate, 0, 0);
	}

	if (Engine::GetDevice().KeyDown(VK_DOWN))
	{
		force_.Stop();
		force_ = DirectX::XMFLOAT3(0, 0, 0);

		rotating_.Value() += DirectX::XMFLOAT3(-KeyRotate, 0, 0);
	}

	if (Engine::GetDevice().KeyDown(VK_LEFT))
	{
		force_.Stop();
		force_ = DirectX::XMFLOAT3(0, 0, 0);

		rotating_.Value() += DirectX::XMFLOAT3(0,-KeyRotate, 0);
	}

	if (Engine::GetDevice().KeyDown(VK_RIGHT))
	{
		force_.Stop();
		force_ = DirectX::XMFLOAT3(0, 0, 0);

		rotating_.Value() += DirectX::XMFLOAT3(0,KeyRotate, 0);
	}

	constexpr auto RotateScaling = 10;
	if (gamming_)
	{
		if (mouseState == MouseState::Down)
		{
			started_ = true;
			force_.Stop();
			force_ = DirectX::XMFLOAT3(0, 0, 0);
			rotating_.Value().y += -mouseDelta.x * RotateScaling;
			rotating_.Value().x += mouseDelta.y * RotateScaling;

			deltas_.Write(mouseDelta * d);

			//Log("Rot", rotating_.Value().x, rotating_.Value().y, rotating_.Value().z);
		}
		else if (mouseState == MouseState::JustDown)
		{
			model_.Alpha().Run(0.25f, 0.15f, 1);
		}
		else if (mouseState == MouseState::JustUp)
		{
			model_.Alpha().Run(1, 0.15f, 1);
			if (std::abs(rotating_.Value().x - answer_.x) < 0.125f && std::abs(rotating_.Value().y - answer_.y) < 0.125f)
			{
				rotating_.Run(answer_, 0.1f, 1);
				gamming_ = false;
				finishedEvent_();
			}
			else
			{
				constexpr auto ForceScaling = 0.1f;
				const auto delta = std::accumulate(deltas_.begin(), deltas_.end(), DirectX::XMFLOAT2(0, 0),
					[](DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b) {
					return LengthSqrt(a) > LengthSqrt(b) ? a : b;
				}) * (1 / max(d, 0.01f)) * ForceScaling;

				std::fill(deltas_.begin(), deltas_.end(), DirectX::XMFLOAT2(0, 0));

				force_ = DirectX::XMFLOAT3
				(
					delta.y * RotateScaling,
					-delta.x * RotateScaling,
					0.0f
				);

				force_.Run(DirectX::XMFLOAT3(0, 0, 0), Clamp(LengthSqrt(force_) * 1000, 0.0f, 1.0f), 1);
			}
		}
	}
}

void Game::GamePlay::RotatingCube::FadeOut()
{
	model_.LightPower().Run(0, 0.25f, 1);
}
