#pragma once
#include "Button.h"
#include "ObjectSet.h"
#include "TaskList.h"
#include "MainBackground.h"


namespace Game
{
	namespace Title
	{
		class StageSelectGUI;
		class StageSelectMenu : public Engine::ObjectSet<Engine::GameObject>
		{
		private:
			Engine::TaskList tl_;

			std::vector<Engine::Button*> btnAniBatch[4];
		public:
			StageSelectMenu(MainBackground& mainBackground, StageSelectGUI& gui);

			void Update(float time) override;

			void Exit();
		};
	}
}