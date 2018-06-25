#pragma once
#include "ObjectSet.h"
namespace Game
{
	namespace GamePlay
	{
		class StageComplete : Engine::ObjectSet<>
		{
		private:

		public:
			StageComplete();

			void Update(float) override;
		};
	}
}