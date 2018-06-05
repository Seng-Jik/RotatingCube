#pragma once
#include "Device.h"
#include "ObjectSet.h"
#include "PostEffect.h"
#include "Shaders.h"
#include "Tween.h"
#include "TaskList.h"
#include "Tex2D.h"
#include "TitleGUI.h"

namespace Game
{
	class MainBackground : public Engine::ObjectSet<Engine::GameObject>
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
		Engine::Tween<float> light_, bkCamera_;
		TitleBackgroundCBuffer pecbcpu_;
		Engine::Rendering::ComPtr<ID3D11Buffer> pecb_;

		bool reciveMouseClick_ = false;

		Engine::Optional<Title::TitleGUI*> titleGUI_;
	public:
		MainBackground();
		void Draw() const override;
		void Update(float time) override;

		void ReturnToLogo();


	};

}
