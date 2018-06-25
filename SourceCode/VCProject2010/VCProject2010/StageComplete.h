#pragma once
#include "ObjectSet.h"
#include "Tween.h"
#include "Sprite2D.h"
#include "TaskList.h"

namespace Game
{
	namespace GamePlay
	{
		class StageComplete : Engine::ObjectSet<>
		{
		private:
			Engine::Rendering::Sprite2D& finishHint_;
			Engine::Tween<float> hintProgress_ = 0;
			Engine::TaskList tl_;
		public:
			StageComplete(Engine::ObjectSet<>* mainBk,std::function<void()> gameMainExit);

			void Update(float) override;
		};
	}
}