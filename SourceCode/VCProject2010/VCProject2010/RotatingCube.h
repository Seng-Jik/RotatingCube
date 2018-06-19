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

			DirectX::XMFLOAT3
				force_ = DirectX::XMFLOAT3(0,0,0),
				rotating_ = DirectX::XMFLOAT3(0,0,0);

		public:
			RotatingCube(const decltype(*Stages)& stage);

			void Update(float d) override;
		};
	}
}