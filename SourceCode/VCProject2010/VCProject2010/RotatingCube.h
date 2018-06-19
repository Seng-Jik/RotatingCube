#pragma once
#include "ObjectSet.h"
#include "ObjModel.h"
#include "StageData.h"

namespace Game
{
	namespace GamePlay
	{
		class RotatingCube : public Engine::ObjectSet<Engine::Rendering::ObjModel>
		{
		private:
			Engine::Rendering::ObjModel& model_;
			
		public:
			RotatingCube(const decltype(*Stages)& stage);

			void Update(float d) override;
		};
	}
}