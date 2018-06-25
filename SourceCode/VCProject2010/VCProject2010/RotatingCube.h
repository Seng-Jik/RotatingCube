#pragma once
#include <functional>
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

			Engine::Tween<DirectX::XMFLOAT3>
				rotating_ = DirectX::XMFLOAT3(0,0,0);

			Engine::Tween<DirectX::XMFLOAT3> 
				force_ = DirectX::XMFLOAT3(0, 0, 0);

			DirectX::XMFLOAT3 answer_;

			Engine::OverwriteArray<DirectX::XMFLOAT2, 256> deltas_;

			bool gamming_ = true;
			bool started_ = false;

			std::function<void()> finishedEvent_;

		public:
			RotatingCube(const decltype(*Stages)& stage);

			void Update(float d) override;

			void FadeOut();

			inline void SetFinishedEvent(decltype(finishedEvent_) f)
			{
				finishedEvent_ = f;
			}

			inline bool Finished() const
			{
				return !gamming_;
			}

			inline bool Started() const
			{
				return started_;
			}
		};
	}
}