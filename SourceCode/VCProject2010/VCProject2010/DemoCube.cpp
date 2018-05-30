#include "stdafx.h"
#include "DemoCube.h"
#include <d3d11.h>
#include "Shaders.h"
#include "Device.h"

using namespace Engine::Rendering;
using namespace Engine;
using namespace DirectX;




Engine::Rendering::Transform Game::EngineTests::DemoCube::buildTransform(const DirectX::XMMATRIX& world)
{
	DirectX::XMVECTOR eye = XMVectorSet(0, 0, 1.5f, 0);
	DirectX::XMVECTOR focus = XMVectorSet(0, 0, -1, 0);
	DirectX::XMVECTOR up = XMVectorSet(0, 1, 0, 0);

	const Engine::Rendering::Transform tsf
	{
		world,
		DirectX::XMMatrixLookAtLH(eye, focus, up),
		GetDevice().Perspective()
	};
	return tsf.Transpose();
}

Game::EngineTests::DemoCube::DemoCube()
{
	ps_ = LoadPShader("ColorOnly");

	
	std::vector<VertexIn> v = 
	{
		//前
		VertexIn{ XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		

		VertexIn{ XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },

		//后
		VertexIn{ XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },

		VertexIn{ XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },

		//左
		VertexIn{ XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT4(0.0f, 0.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		

		VertexIn{ XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT4(0.0f, 0.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT4(0.0f, 0.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },

		//右
		VertexIn{ XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT4(1.0f, 1.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT4(1.0f, 1.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(1.0f, 1.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },

		VertexIn{ XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(1.0f, 1.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT4(1.0f, 1.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT4(1.0f, 1.0f, 0.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },

		//上
		VertexIn{ XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },

		VertexIn{ XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },

		//下
		VertexIn{ XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT4(1.0f, 0.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT4(1.0f, 0.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT4(1.0f, 0.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		
		VertexIn{ XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT4(1.0f, 0.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT4(1.0f, 0.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		VertexIn{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT4(1.0f, 0.0f, 1.0f,1.0f), XMFLOAT2(0.5f, 0.5f) },
		
	};

	vb_ = VertexIn::CreateBuffer(v);
	vbSize_ = v.size();

	constBuffer_ = CreateConstantBuffer(buildTransform(DirectX::XMMatrixIdentity()));
}

void Game::EngineTests::DemoCube::Update(float deltaTime)
{
}

void Game::EngineTests::DemoCube::Draw() const
{
	auto& ctx = GetDevice().Context();

	auto pcb = constBuffer_.Get();
	ctx.VSSetConstantBuffers(0, 1,&pcb );
	ctx.PSSetShader(ps_.Get(), nullptr, 0);

	auto buf = vb_.Get();
	const UINT stride[] = { sizeof(VertexIn) };
	const UINT offset[] = { 0 };

	ctx.IASetVertexBuffers(0, 1, &buf, stride, offset);
	ctx.Draw(vbSize_, 0);
}

void Game::EngineTests::DemoCube::SetRotation(float x, float y, float z)
{
	UpdateBuffer(constBuffer_,
		buildTransform(
			DirectX::XMMatrixRotationX(x) * 
			DirectX::XMMatrixRotationY(y) * 
			DirectX::XMMatrixRotationZ(z)
		)
	);
}
