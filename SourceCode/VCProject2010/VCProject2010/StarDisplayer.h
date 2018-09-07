#pragma once
#include "ObjectSet.h"
#include "Sprite2D.h"
#include "Tween.h"

namespace Game
{
	namespace GamePlay
	{
		class StarDisplayer : public Engine::ObjectSet<Engine::Rendering::Sprite2D>
		{
		private:
			const int starNum_;
			Engine::Tween<float> alpha_;
		public:
			StarDisplayer(float x,float y,float time,float zoom);

			void Update(float t) override;
		};
	}
}
