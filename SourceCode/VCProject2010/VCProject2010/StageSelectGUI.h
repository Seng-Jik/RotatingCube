#pragma once
#include "GameObject.h"
#include "ObjectSet.h"
#include "Button.h"

namespace Game
{
	namespace Title
	{
		class StageSelectGUI : public Engine::ObjectSet<Engine::GameObject>
		{
		private:
			Engine::Button& back_;

		public:
			StageSelectGUI();
		};
	}
}
