#pragma once
#include <string>
#include <wrl/client.h>
#include <d3d11.h>

namespace Engine
{
	namespace Rendering
	{
		using Microsoft::WRL::ComPtr;

		using PtrPShader = ComPtr<ID3D11PixelShader>;
		using PtrGShader = ComPtr<ID3D11GeometryShader>;

		PtrPShader LoadPShader(const std::string& name);
		PtrGShader LoadGShader(const std::string& name);
	}
}