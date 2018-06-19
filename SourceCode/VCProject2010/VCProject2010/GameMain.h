#pragma once
#include "ObjectSet.h"
#include "ObjModel.h"
#include "StageData.h"
#include "RotatingCube.h"

namespace Game
{
	namespace GamePlay
	{
		class GameMain : public Engine::ObjectSet<Engine::GameObject>
		{
		private:
			RotatingCube& rotCube_;

		public:
			GameMain(const decltype(*Stages)& stage);
		};
	}
}