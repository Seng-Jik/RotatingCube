#include "stdafx.h"
#include "Cube.h"
#include <d3d11.h>
#include "Shaders.h"
#include "Device.h"

using namespace Engine::Rendering;
using namespace DirectX;


struct Transform
{
	XMMATRIX world;
	XMMATRIX view;
	XMMATRIX prj;
};

Game::EngineTests::Cube::Cube()
{
	ps_ = LoadPShader("Green");
	
	std::vector<VertexIn> v = 
	{
		//Ç°
		VertexIn{ XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT4(0.0f, 0.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },

		VertexIn{ XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT4(0.0f, 0.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },

		//ºó
		VertexIn{ XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },

		VertexIn{ XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },

		//×ó
		VertexIn{ XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },

		VertexIn{ XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT4(0.0f, 0.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },

		//ÓÒ
		VertexIn{ XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },

		VertexIn{ XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT4(0.0f, 0.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) }
	};

	buf_ = VertexIn::CreateBuffer(v);

	Transform tsf;

	constBuffer_ = CreateConstantBuffer(tsf);
}

void Game::EngineTests::Cube::Update(float deltaTime)
{
	rot_ += 1.0f * deltaTime;

	DirectX::XMVECTOR eye = XMVectorSet(0, 0, -8.0f, 0);
	DirectX::XMVECTOR focus = XMVectorSet(0, 0, 1, 0);
	DirectX::XMVECTOR up = XMVectorSet(0, 1, 0, 0);

	Transform tsf;
	tsf.world = DirectX::XMMatrixRotationY(rot_);
	tsf.view = DirectX::XMMatrixLookAtLH(eye, focus, up);
	tsf.prj = GetDevice().Perspective();

	UpdateBuffer(constBuffer_, tsf);
}

void Game::EngineTests::Cube::Draw() const
{
	auto& ctx = GetDevice().Context();

	auto pcb = constBuffer_.Get();
	ctx.VSSetConstantBuffers(0, 1,&pcb );
	ctx.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	ctx.PSSetShader(ps_.Get(), nullptr, 0);

	auto buf = buf_.Get();
	const UINT stride[] = { sizeof(VertexIn) };
	const UINT offset[] = { 0 };

	ctx.IASetVertexBuffers(0, 1, &buf, stride, offset);
	ctx.Draw(24, 0);
}
