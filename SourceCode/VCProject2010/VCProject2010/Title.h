#pragma once
#include "Device.h"
#include "GameObject.h"
#include "PostEffect.h"
#include "Shaders.h"
#include "Tween.h"
#include "TaskList.h"

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
				float iLight;
				float a, b, c;
			};

			Engine::TaskList tl_;
			Engine::Tween<float> light_;
			TitleBackgroundCBuffer pecbcpu_;
			Engine::Rendering::ComPtr<ID3D11Buffer> pecb_;
		public:
			Title();
			void Draw() const override;
			void Update(float time) override;
		};
	}
}