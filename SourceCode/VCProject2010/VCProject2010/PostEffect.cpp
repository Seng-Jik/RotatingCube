#include "stdafx.h"
#include "PostEffect.h"
#include "Shaders.h"
#include "Device.h"

using namespace DirectX;

Engine::Rendering::PostEffect::PostEffect(const char * peps):
	peps_ { LoadPShader(peps) },
	vb_ { VertexIn::CreateBuffer(std::vector<VertexIn>
{
	VertexIn{ XMFLOAT3(-1, -1, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f), XMFLOAT2(0, 0) },
	VertexIn{ XMFLOAT3(-1, 1, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f), XMFLOAT2(0, 1) },
	VertexIn{ XMFLOAT3(1, -1, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f), XMFLOAT2(1, 0) },

	VertexIn{ XMFLOAT3(1, 1, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f), XMFLOAT2(1, 1) },
	VertexIn{ XMFLOAT3(1, -1, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f), XMFLOAT2(1, 0) },
	VertexIn{ XMFLOAT3(-1, 1, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f), XMFLOAT2(0, 1) }
}) }
{
	Rendering::Transform t{
		DirectX::XMMatrixIdentity(),
		DirectX::XMMatrixIdentity(),
		DirectX::XMMatrixIdentity()
	};

	vscb_ = Rendering::CreateConstantBuffer(t.Transpose());
}

void Engine::Rendering::PostEffect::SetConstantBuffer(const ComPtr<ID3D11Buffer>& cb)
{
	pscb_ = cb;
}

void Engine::Rendering::PostEffect::Draw() const
{
	auto& d = Engine::GetDevice();
	d.Context().VSSetConstantBuffers(0, 1, vscb_.GetAddressOf());
	d.Context().PSSetConstantBuffers(0, 1, pscb_.GetAddressOf());
	d.Context().PSSetShader(peps_.Get(), nullptr, 0);

	auto buf = vb_.Get();
	const UINT stride[] = { sizeof(VertexIn) };
	const UINT offset[] = { 0 };

	d.Context().IASetVertexBuffers(0, 1, &buf, stride, offset);
	d.Context().Draw(6, 0);
}

