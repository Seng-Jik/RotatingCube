#pragma once
#include "ObjectSet.h"
#include "Sprite2D.h"

namespace Game
{
	namespace GamePlay
	{
		class StarDisplayer : public Engine::ObjectSet<Engine::Rendering::Sprite2D>
		{
		public:
			StarDisplayer();

			void Update(float t) override;
		};
	}
}
