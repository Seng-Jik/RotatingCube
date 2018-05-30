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
		public:
			inline BlueScreen() : pe_{ "ColorOnly" } {}
			virtual void Draw() const
			{
				const float blue[4] = { 0,0,1,1 };
				auto& device = Engine::GetDevice();
				device.Context().ClearRenderTargetView(&device.RenderTargetView(), blue);
			}
		};
	}
}