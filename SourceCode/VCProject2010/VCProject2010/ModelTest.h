#pragma once
#include "ObjModel.h"
#include "ObjectSet.h"
namespace Game
{
	namespace EngineTests
	{
		class ModelTest : public Engine::ObjectSet<Engine::Rendering::ObjModel>
		{
		private:
			Engine::Rendering::ObjModel& model_;

			float rotX_ = 0, rotY_ = 0, rotZ_ = 0;
		public:
			ModelTest(const char*);
			void Draw() const override;
			void Update(float) override;
		};
	}
}
