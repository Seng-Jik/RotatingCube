#include "stdafx.h"
#include "Tex2D.h"
#include <fstream>

using namespace Engine::Rendering;

std::tuple<PtrTex2D, DirectX::XMINT2> Engine::Rendering::LoadTex2D(const char * texName)
{
	std::ifstream in(texName + std::string(".sst"), std::ios::binary);
	Must(in.good());

	in.get();	//Compress Mode

	uint16_t rectSize;
	in.read((char*)&rectSize, sizeof(rectSize));

	uint16_t w, h;
	in.read((char*)&w, sizeof(w));
	in.read((char*)&h, sizeof(h));

	uint16_t ignore[4];
	for (uint16_t i = 0; i < rectSize; ++i)
		in.read((char*)ignore, sizeof(ignore));

	int32_t dataSize;
	in.read((char*)&dataSize, sizeof(dataSize));

	std::vector<unsigned char> pixels;
	pixels.resize(dataSize);
	in.read((char*)pixels.data(), pixels.size());
	
	D3D11_TEXTURE2D_DESC desc = { 0 };
	desc.Width = w;
	desc.Height = h;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.ArraySize = 1;
	desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;

	
	D3D11_SUBRESOURCE_DATA data = { 0 };
	data.pSysMem = pixels.data();
	data.SysMemPitch = w * 4;

	PtrTex2D ret;
	const auto res = Engine::GetDevice().D3DDevice().CreateTexture2D(&desc, &data, ret.GetAddressOf());
	Must(SUCCEEDED(res));

	return std::make_tuple(ret,DirectX::XMINT2(w,h));
}

PtrTex2DShaderResView Engine::Rendering::CreateShaderResView(const PtrTex2D & p)
{
	PtrTex2DShaderResView ret;
	D3D11_SHADER_RESOURCE_VIEW_DESC desc;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipLevels = -1;
	desc.Texture2D.MostDetailedMip = 0;
	Engine::GetDevice().D3DDevice().CreateShaderResourceView(p.Get(), &desc, ret.GetAddressOf());
	return ret;
}

PtrSampler Engine::Rendering::CreateSampler(D3D11_SAMPLER_DESC desc)
{
	PtrSampler smp;
	Engine::GetDevice().D3DDevice().CreateSamplerState(&desc,smp.GetAddressOf());
	return smp;
}
