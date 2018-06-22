#pragma once
#include "ObjectSet.h"
#include "ObjModel.h"
#include "StageData.h"
#include "RotatingCube.h"
#include "TaskList.h"
#include "Clock.h"
#include "AnswerBoard.h"

namespace Game
{
	namespace GamePlay
	{
		class GameMain : public Engine::ObjectSet<Engine::GameObject>
		{
		private:
			RotatingCube* rotCube_;
			AnswerBoard* ansBoard_;
			Engine::TaskList tasks_;

			Clock& clk_;
			float timer_ = -1;
		public:
			GameMain(const decltype(*Stages)& stage);

			void Update(float d);
		};
	}
}