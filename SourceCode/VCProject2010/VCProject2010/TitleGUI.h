#pragma once
#include "Device.h"
#include "ObjectSet.h"
#include "PostEffect.h"
#include "Shaders.h"
#include "Tween.h"
#include "TaskList.h"
#include "Tex2D.h"
#include "Sprite2D.h"
#include "TaskList.h"

namespace Game
{
	namespace Title
	{
		class TitleGUI : public Engine::ObjectSet<Engine::Rendering::Sprite2D>
		{
		private:
			Engine::Rendering::Sprite2D &logo_,&hint_;
			Engine::Tween<float> logoAnimationTween_,hintAlphaMul_;

			Engine::TaskList tl_;
			float timer_ = 0;

			bool live_ = true;

			Engine::Rendering::Sprite2D& about_;
		public:
			TitleGUI();
			void Update(float time) override;
			void Click();
		};
	}
}
