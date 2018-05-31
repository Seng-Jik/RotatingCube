#pragma once
#include "GameObject.h"
#include "Device.h"
namespace Engine
{
	namespace Rendering
	{
		class Sprite : public GameObject
		{
		private:

		public:
			Sprite(const Sprite&) = delete;
			const Sprite& operator = (const Sprite&) = delete;

			Sprite(const char* tex);
			void SetColorMod(DirectX::XMFLOAT3 rgb);
			void SetAlpha(float a);
			void SetZoom(float zoom);
			void SetPos(float x, float y);
		};
	}
}