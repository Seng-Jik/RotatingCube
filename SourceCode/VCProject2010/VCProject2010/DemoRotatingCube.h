#pragma once
#include "ObjectSet.h"
#include "DemoCube.h"

namespace Game
{
	namespace EngineTests
	{
		class DemoRotatingCube : public Engine::ObjectSet<DemoCube>
		{
		private:
			DemoCube & cube_;

			float x_, y_, z_;
		public:
			DemoRotatingCube();

			void Update(float) override;
		};
	}
}
