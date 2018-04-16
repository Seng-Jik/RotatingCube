#pragma once
#include "Device.h"
#include "GameObject.h"

namespace Game
{
	namespace EngineTests
	{
		class BlueScreen : public Engine::GameObject
		{
		public:
			virtual void Draw() const
			{
				const float blue[4] = { 0,0,1,1 };
				auto& device = Engine::Rendering::GetDevice();
				device.Context().ClearRenderTargetView(&device.RenderTargetView(), blue);
			}
		};
	}
}