#pragma once
#include "ObjectSet.h"
#include "Button.h"
#include "TaskList.h"
#include "MainBackground.h"
#include "ObjModel.h"
namespace Game
{
	namespace Title
	{
		class Help : public Engine::ObjectSet<Engine::GameObject>
		{
		private:
			Engine::Button & back_;
			Engine::TaskList tl_;

			Engine::Rendering::Sprite2D& helpHint_;
			Engine::Tween<float> helpHintAlpha_;

			Engine::Rendering::ObjModel& board_;
		public:
			Help(MainBackground& t);
			void Update(float d) override;
		};
	}
}