#pragma once
#include "Device.h"
#include <tuple>

namespace Engine
{
	namespace Rendering
	{
		using PtrTex2D = ComPtr<ID3D11Texture2D>;
		using PtrRTView = ComPtr<ID3D11RenderTargetView>;
		using PtrTex2DShaderResView = ComPtr<ID3D11ShaderResourceView>;
		using PtrSampler = ComPtr<ID3D11SamplerState>;

		std::tuple<PtrTex2D,DirectX::XMINT2> LoadTex2D(const char* texName);
		std::tuple<PtrTex2D, PtrRTView, DirectX::XMINT2> CreateRTTTex();

		PtrTex2DShaderResView CreateShaderResView(const PtrTex2D& p, D3D11_SRV_DIMENSION vd = D3D11_SRV_DIMENSION_TEXTURE2D);
		PtrSampler CreateSampler(D3D11_SAMPLER_DESC desc);
	}
}