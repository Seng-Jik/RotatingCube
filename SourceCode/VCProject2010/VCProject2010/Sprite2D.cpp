#include "stdafx.h"
#include "Sprite2D.h"
#include "Device.h"

using namespace Engine::Rendering;


PtrCBuffer Engine::Rendering::Sprite::getCBuffer()
{
	static const Transform tsf {
		DirectX::XMMatrixIdentity(),
		DirectX::XMMatrixOrthographicLH(800,600,0,1),
		Engine::GetDevice().Perspective()
	};

	static auto cb = Engine::Rendering::CreateConstantBuffer(tsf.Transpose());
	return cb;
}

Engine::Rendering::Sprite::Sprite(const char * tex) :
	tex_ { LoadTex2D(tex) }
{
}

void Engine::Rendering::Sprite::SetColorMod(DirectX::XMFLOAT3 rgb)
{
}

void Engine::Rendering::Sprite::SetAlpha(float a)
{
}

void Engine::Rendering::Sprite::SetZoom(float zoom)
{
}

void Engine::Rendering::Sprite::SetPos(float x, float y)
{
}

void Engine::Rendering::Sprite::Draw() const
{
}
