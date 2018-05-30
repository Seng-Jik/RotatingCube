#pragma once
#include <string>
#include <wrl/client.h>
#include <d3d11.h>

namespace Engine
{
	namespace Rendering
	{
		using Microsoft::WRL::ComPtr;

		ComPtr<ID3D11PixelShader> LoadPShader(const std::string& name);
	}
}