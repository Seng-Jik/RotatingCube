#pragma once
#include "ObjectSet.h"
#include "ObjModel.h"
#include "StageData.h"
#include "RotatingCube.h"
#include "TaskList.h"

namespace Game
{
	namespace GamePlay
	{
		class GameMain : public Engine::ObjectSet<Engine::GameObject>
		{
		private:
			RotatingCube* rotCube_;
			Engine::TaskList tasks_;
		public:
			GameMain(const decltype(*Stages)& stage);

			void Update(float d);
		};
	}
}