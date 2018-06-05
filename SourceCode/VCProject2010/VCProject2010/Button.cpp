#include "stdafx.h"
#include "Button.h"

void Engine::Button::Update(float time) 
{
	alpha_.Update(time);
	zoom_.Update(time);
	posX_.Update(time);
	posY_.Update(time);

	SetPos(posX_, posY_);
	SetZoom(zoom_);
	SetAlpha(alpha_);

	
	bool mouseBtnDown;
	DirectX::XMFLOAT2 mousePos;
	std::tie(mouseBtnDown, mousePos) = Engine::GetDevice().Mouse();
	mousePos.x *= 800;
	mousePos.y *= 600;
	mousePos.x -= 400;
	mousePos.y -= 300;
	mousePos.y = -mousePos.y;

	auto spRect = GetSpriteRect();
	const bool mouseInRect =
		mousePos.x > spRect.x && mousePos.y > spRect.y &&
		mousePos.x < spRect.z && mousePos.y < spRect.w;

	if (mouseInRect != lastMode)
	{
		lastMode = mouseInRect;

		zoom_.Run(mouseInRect ? 0.75F : 0.5F, 0.25F, 1);
	}
}
