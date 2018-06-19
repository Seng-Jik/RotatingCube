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
		private:
			decltype(*Stages)& stageData_;
		public:
			GameMain(const decltype(*Stages)& stage);
			void Draw() const override;
			void Update(float d) override;
		};
	}
}