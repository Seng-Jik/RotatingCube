#pragma once
#include "GameObject.h"
#include "ObjectSet.h"
#include "Button.h"
#include "Title.h"
#include "TaskList.h"

namespace Game
{
	namespace Title
	{
		class StageSelectGUI : public Engine::ObjectSet<Engine::GameObject>
		{
		private:
			Engine::Button& back_;
			Engine::TaskList tl_;
		public:
			StageSelectGUI(Title& t);
			void Update(float time) override;
		};
	}
}
