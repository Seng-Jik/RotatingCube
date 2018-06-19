#pragma once
#include "ObjectSet.h"
#include "ObjModel.h"
#include "StageData.h"

namespace Game
{
	namespace GamePlay
	{
		class GameMain : public Engine::ObjectSet<Engine::GameObject>
		{
		public:
			GameMain(decltype(*Stages) stage);
			void Draw() const override;
			void Update(float d) override;
		};
	}
}