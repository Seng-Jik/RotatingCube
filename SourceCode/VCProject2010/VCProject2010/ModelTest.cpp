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

	bool isDown;
	DirectX::XMFLOAT2 mpos;
	std::tie(isDown, mpos) = Engine::GetDevice().Mouse();

	if (isDown)
	{
		rotX_ = mpos.y * 4;
		rotY_ = mpos.x * 4;
		model_.SetRotating(rotX_, rotY_, rotZ_);
	}
}
