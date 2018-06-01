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
	colorMod_.x = rgb.x;
	colorMod_.y = rgb.y;
	colorMod_.z = rgb.z;
}

void Engine::Rendering::Sprite::SetAlpha(float a)
{
	colorMod_.w = a;
}

void Engine::Rendering::Sprite::SetZoom(float zoom)
{
	zoom_ = zoom;
}

void Engine::Rendering::Sprite::SetPos(float x, float y)
{
	position_.x = x;
	position_.y = y;
}

void Engine::Rendering::Sprite::Draw() const
{
	
}
