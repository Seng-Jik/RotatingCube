#pragma once
#include "ObjectSet.h"
#include "ObjModel.h"
#include "StageData.h"
#include "OverwriteArray.h"

namespace Game
{
	namespace GamePlay
	{
		class RotatingCube : public Engine::ObjectSet<Engine::Rendering::ObjModel>
		{
		private:
			Engine::Rendering::ObjModel& model_;

			DirectX::XMFLOAT3
				rotating_ = DirectX::XMFLOAT3(0,0,0);

			Engine::Tween<DirectX::XMFLOAT3> 
				force_ = DirectX::XMFLOAT3(0, 0, 0);

			Engine::OverwriteArray<DirectX::XMFLOAT2, 256> deltas_;

		public:
			RotatingCube(const decltype(*Stages)& stage);

			void Update(float d) override;
		};
	}
}