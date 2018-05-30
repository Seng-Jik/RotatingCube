#include "stdafx.h"
#include "Shaders.h"
#include "Device.h"
#include "Assets.h"

using namespace Engine::Rendering;

ComPtr<ID3D11PixelShader> Engine::Rendering::LoadPShader(const std::string & name)
{
	ComPtr<ID3D11PixelShader> ret;

	auto buf = Engine::LoadAssets("PS" + name + ".cso");

	Must(SUCCEEDED(Engine::GetDevice().D3DDevice().CreatePixelShader(
		buf.data(),
		buf.size(),
		nullptr,
		ret.GetAddressOf()
	)));

	return ret;
}
