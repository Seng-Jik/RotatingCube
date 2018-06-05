#pragma once
#include "Button.h"
#include "ObjectSet.h"
#include "TaskList.h"

namespace Game
{
	namespace Title
	{
		class StageSelectMenu : public Engine::ObjectSet<Engine::Button>
		{
		private:
			Engine::TaskList tl_;

			std::vector<Engine::Button*> btnAniBatch[4];
		public:
			StageSelectMenu();

			void Update(float time) override;

			void ReturnToLogo();
		};
	}
}