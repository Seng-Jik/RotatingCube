#pragma once
#include "ObjectSet.h"
#include "Tween.h"
#include "Sprite2D.h"
#include "TaskList.h"
#include "StageData.h"
namespace Game
{
	namespace GamePlay
	{
		class StageComplete : public Engine::ObjectSet<>
		{
		private:
			Engine::Rendering::Sprite2D& finishHint_;
			Engine::Tween<float> hintProgress_ = 0;
			Engine::TaskList tl_;
		public:
			StageComplete(float time,StageName stg, StageName nextStg,Engine::ObjectSet<>* mainBk,std::function<void()> gameMainExit);

			void Update(float) override;
		};
	}
}