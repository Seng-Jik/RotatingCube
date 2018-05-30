#pragma once
#include "Device.h"
#include "GameObject.h"
#include "PostEffect.h"
#include "Shaders.h"
namespace Game
{
	namespace EngineTests
	{
		class BlueScreen : public Engine::GameObject
		{
		private:
			Engine::Rendering::PostEffect pe_;

			struct TitleBackgroundCBuffer
			{
				float iTime;
				DirectX::XMFLOAT2 iMouse;
				float iWdivH;
			};

			TitleBackgroundCBuffer pecbcpu_;
			Engine::Rendering::ComPtr<ID3D11Buffer> pecb_;
		public:
			inline BlueScreen() : 
				pe_{ "TitleBackground" } ,
				pecbcpu_ { 0,DirectX::XMFLOAT2(0,0),800.0f/600.0f },
				pecb_{ Engine::Rendering::CreateConstantBuffer(pecbcpu_) }
			{
				pe_.SetConstantBuffer(pecb_);
			}

			void Draw() const override
			{
				Engine::Rendering::UpdateBuffer(pecb_, pecbcpu_);
				pe_.Draw();
			}

			void Update(float time) override
			{
				pecbcpu_.iTime += time;
			}
		};
	}
}