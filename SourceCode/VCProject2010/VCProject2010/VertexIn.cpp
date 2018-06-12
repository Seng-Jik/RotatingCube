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

PtrVBuffer Engine::Rendering::VertexIn::CreateIBuffer(const size_t * ib, size_t size)
{
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * size;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = ib;

	PtrVBuffer ibo;
	Must(SUCCEEDED(Engine::GetDevice().D3DDevice().CreateBuffer(&ibd, &iinitData, ibo.GetAddressOf())));
	return ibo;
}

void Engine::Rendering::VertexIn::UpdateVBuffer(const PtrVBuffer & vb, const VertexIn * vin)
{
	GetDevice().Context().UpdateSubresource(vb.Get(), 0, nullptr, vin, 0, 0);
}
