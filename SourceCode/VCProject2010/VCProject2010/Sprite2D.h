#pragma once
#include "GameObject.h"
#include "Device.h"
#include "Tex2D.h"
#include "VertexIn.h"

namespace Engine
{
	namespace Rendering
	{
		class Sprite : public GameObject
		{
		private:
			DirectX::XMFLOAT4 colorMod_;
			DirectX::XMFLOAT2 position_;
			float zoom_;
			std::array<VertexIn, 6> vbcpu_;
			Engine::Rendering::PtrTex2D tex_;
			Engine::Rendering::PtrVBuffer vb_;
			

			static PtrCBuffer getCBuffer();

		public:
			Sprite(const Sprite&) = delete;
			const Sprite& operator = (const Sprite&) = delete;

			Sprite(const char* tex);
			void SetColorMod(DirectX::XMFLOAT3 rgb);
			void SetAlpha(float a);
			void SetZoom(float zoom);
			void SetPos(float x, float y);
			void Draw() const override;
		};
	}
}