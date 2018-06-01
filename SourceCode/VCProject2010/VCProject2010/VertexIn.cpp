#include "stdafx.h"
#include "VertexIn.h"
#include "Device.h"

using namespace Engine::Rendering;


PtrVBuffer Engine::Rendering::VertexIn::CreateVBuffer(const std::vector<VertexIn>& vtx)
{
	return Engine::Rendering::VertexIn::CreateVBuffer(vtx.data(), vtx.size());
}

PtrVBuffer Engine::Rendering::VertexIn::CreateVBuffer(const VertexIn* vtx, size_t size)
{
	PtrVBuffer buf;

	D3D11_BUFFER_DESC bd{ 0 };
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VertexIn) * size;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;


	D3D11_SUBRESOURCE_DATA initData{ 0 };
	initData.pSysMem = vtx;
	Must(SUCCEEDED(GetDevice().D3DDevice().CreateBuffer(&bd, &initData, buf.GetAddressOf())));

	return buf;
}
