#include "stdafx.h"
#include "ModelTest.h"

Game::EngineTests::ModelTest::ModelTest(const char * modelName):
	model_ { NewObject<Engine::Rendering::ObjModel>(modelName) }
{
	model_.SetCenterOffset(0, 0, -20);
	model_.SetScale(1);
}

void Game::EngineTests::ModelTest::Draw() const
{
	Engine::ObjectSet<Engine::Rendering::ObjModel>::Draw();
}

void Game::EngineTests::ModelTest::Update(float d)
{
	Engine::ObjectSet<Engine::Rendering::ObjModel>::Update(d);

	Engine::MouseState mouseState;
	DirectX::XMFLOAT2 mpos;
	std::tie(mouseState, mpos) = Engine::GetDevice().Mouse();

	if (mouseState == Engine::MouseState::Down)
	{
		rotX_ = mpos.y * 4;
		rotY_ = mpos.x * 4;
		model_.SetRotating(rotX_, rotY_, rotZ_);
	}
}
