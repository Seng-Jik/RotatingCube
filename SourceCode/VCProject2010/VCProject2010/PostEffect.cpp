#include "stdafx.h"
#include "PostEffect.h"
#include "Shaders.h"
#include "Device.h"

using namespace DirectX;
using namespace Engine::Rendering;

std::tuple<PtrCBuffer, PtrVBuffer> Engine::Rendering::PostEffect::getVSBuffers()
{
	static PtrVBuffer vb{ VertexIn::CreateVBuffer(std::array<VertexIn,6>
	{
		VertexIn{ XMFLOAT3(-1, -1, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f), XMFLOAT2(0, 0) },
			VertexIn{ XMFLOAT3(-1, 1, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f), XMFLOAT2(0, 1) },
			VertexIn{ XMFLOAT3(1, -1, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f), XMFLOAT2(1, 0) },

			VertexIn{ XMFLOAT3(1, 1, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f), XMFLOAT2(1, 1) },
			VertexIn{ XMFLOAT3(1, -1, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f), XMFLOAT2(1, 0) },
			VertexIn{ XMFLOAT3(-1, 1, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f), XMFLOAT2(0, 1) }
	}) };
	
	static const Rendering::Transform t{
		DirectX::XMMatrixIdentity(),
		DirectX::XMMatrixIdentity(),
		DirectX::XMMatrixIdentity()
	};

	const static auto vscb = Rendering::CreateConstantBuffer(t.Transpose());

	static auto ret = std::make_tuple(vscb, vb);

	return ret;
}

Engine::Rendering::PostEffect::PostEffect(const char * peps):
	peps_ { LoadPShader(peps) }
{
	
}

void Engine::Rendering::PostEffect::SetConstantBuffer(const ComPtr<ID3D11Buffer>& cb)
{
	pscb_ = cb;
}

void Engine::Rendering::PostEffect::Draw() const
{
	PtrCBuffer vscb;
	PtrVBuffer vb;
	std::tie(vscb, vb) = getVSBuffers();

	auto& d = Engine::GetDevice();
	d.Context().VSSetConstantBuffers(0, 1, vscb.GetAddressOf());
	d.Context().PSSetConstantBuffers(0, 1, pscb_.GetAddressOf());
	d.Context().PSSetShader(peps_.Get(), nullptr, 0);

	auto buf = vb.Get();
	const UINT stride[] = { sizeof(VertexIn) };
	const UINT offset[] = { 0 };

	d.Context().IASetVertexBuffers(0, 1, &buf, stride, offset);
	d.Context().Draw(6, 0);
}

