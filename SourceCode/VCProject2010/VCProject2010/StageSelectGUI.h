#pragma once
#include "GameObject.h"
#include "ObjectSet.h"
#include "Button.h"
#include "MainBackground.h"
#include "TaskList.h"
#include "StageSelectMenu.h"

namespace Game
{
	namespace Title
	{
		class StageSelectGUI : public Engine::ObjectSet<Engine::GameObject>
		{
		private:
			Engine::Button& back_;
			Engine::TaskList tl_;
			StageSelectMenu& menu_;
		public:
			StageSelectGUI(MainBackground& t);
			void Update(float time) override;
		};
	}
}
