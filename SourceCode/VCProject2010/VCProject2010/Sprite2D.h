#pragma once
#include "GameObject.h"
#include "Device.h"
#include "Tex2D.h"
#include "VertexIn.h"

namespace Engine
{
	namespace Rendering
	{
		class Sprite2D : public GameObject
		{
		private:
			DirectX::XMFLOAT4 colorMod_ = { 1,1,1,1 };
			DirectX::XMFLOAT2 position_{ 0,0, };
			float zoom_ = 1.0f;
			mutable std::array<VertexIn, 6> vbcpu_;
			const Engine::Rendering::PtrTex2D tex_;
			const Engine::Rendering::PtrTex2DShaderResView texResView_;
			Engine::Rendering::PtrVBuffer vb_ = VertexIn::CreateVBuffer(vbcpu_);
			
			mutable bool updatevb_ = true;
			const DirectX::XMINT2 size_;

			static ID3D11Buffer* getCBuffer();
			static ComPtr<ID3D11PixelShader> getPShader();
			static ComPtr<ID3D11SamplerState> getSamplerState();
			static ComPtr<ID3D11BlendState> createBlendState();
			static ComPtr<ID3D11BlendState> getBlendState();

		public:
			Sprite2D(const Sprite2D&) = delete;
			const Sprite2D& operator = (const Sprite2D&) = delete;

			Sprite2D(const char* tex);
			void SetColorMod(DirectX::XMFLOAT3 rgb);
			void SetAlpha(float a);
			void SetZoom(float zoom);
			void SetPos(float x, float y);
			void Draw() const override;
		};
	}
}