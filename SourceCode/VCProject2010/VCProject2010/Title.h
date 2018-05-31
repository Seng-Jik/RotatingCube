#pragma once
#include "Device.h"
#include "GameObject.h"
#include "PostEffect.h"
#include "Shaders.h"
namespace Game
{
	namespace Title
	{
		class Title : public Engine::GameObject
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
			Title();
			void Draw() const override;
			void Update(float time) override;
		};
	}
}