#pragma once
#include "GameObject.h"

namespace Game
{
	namespace EngineTests
	{
		class Cube : public Engine::GameObject
		{
		private:

		public:
			Cube();
			void Update(float) override;
			void Draw() const override;
		};
	}
}