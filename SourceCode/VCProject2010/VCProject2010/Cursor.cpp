#include "stdafx.h"
#include "Cursor.h"
#include "Device.h"

Engine::Cursor::Cursor() :
	Rendering::Sprite2D { "cursor" }
{
	alpha_ = 0;

	SetZoom(0.5f);
}

void Engine::Cursor::Show()
{
	alpha_.Run(1, 0.5f, 1);
}

void Engine::Cursor::Hide()
{
	alpha_.Run(0, 0.5f, 1);
}

void Engine::Cursor::Update(float time)
{
	alpha_.Update(time);
	SetAlpha(alpha_);

	auto screenSize = Engine::GetDevice().GetScreenSize();

	DirectX::XMFLOAT2 pos;
	std::tie(std::ignore, pos) = Engine::GetDevice().Mouse();
	pos.x -= 0.5f;
	pos.y -= 0.5f;
	pos.x *= 800;
	pos.y *= -600;
	SetPos(pos.x, pos.y);
}
