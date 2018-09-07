#include "stdafx.h"
#include "StarDisplayer.h"

using namespace Engine;
using namespace Engine::Rendering;


Game::GamePlay::StarDisplayer::StarDisplayer(float x,float y,float time, float zoom) :
	starNum_ { time < 2.0f ? 3 : (time < 6.0f ? 2 : (time < 10.0f ? 1 : 0))}
{
	alpha_ = 0;
	alpha_.Run(1, 0.5f, 1);
	zoom *= 0.5f;

	auto& l = NewObject<Sprite2D>(starNum_ >= 1 ? "filled" : "empty");
	auto& c = NewObject<Sprite2D>(starNum_ >= 2 ? "filled" : "empty");
	auto& r = NewObject<Sprite2D>(starNum_ >= 3 ? "filled" : "empty");

	l.SetPos(x - 200 * zoom, y);
	c.SetPos(x, y);
	r.SetPos(x + 200 * zoom, y);

	l.SetZoom(zoom);
	c.SetZoom(zoom);
	r.SetZoom(zoom);
}

void Game::GamePlay::StarDisplayer::Update(float t)
{
	ObjectSet<Sprite2D>::Update(t);

	alpha_.Update(t);

	for (auto& obj : *this)
	{
		obj.get()->SetAlpha(alpha_);
	}
}
