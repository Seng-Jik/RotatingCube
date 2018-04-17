#include "stdafx.h"
#include "VertexIn.h"
#include "Device.h"

using namespace Engine::Rendering;


ComPtr<ID3D11Buffer> Engine::Rendering::VertexIn::CreateBuffer(const std::vector<VertexIn>& vtx)
{
	ComPtr<ID3D11Buffer> buf;

	D3D11_BUFFER_DESC bd{ 0 };
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VertexIn) * vtx.size();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;


	D3D11_SUBRESOURCE_DATA initData{ 0 };
	initData.pSysMem = vtx.data();
	Must(SUCCEEDED(GetDevice().D3DDevice().CreateBuffer(&bd, &initData, buf.GetAddressOf())));

	return buf;
}
