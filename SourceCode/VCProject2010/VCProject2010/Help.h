#pragma once
#include "ObjectSet.h"
#include "Button.h"
#include "TaskList.h"
#include "MainBackground.h"
namespace Game
{
	namespace Title
	{
		class Help : public Engine::ObjectSet<Engine::GameObject>
		{
		private:
			Engine::Button & back_;
			Engine::TaskList tl_;
		public:
			Help(MainBackground& t);
			void Update(float d) override;
		};
	}
}