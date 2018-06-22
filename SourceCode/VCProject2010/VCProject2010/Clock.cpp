#include "stdafx.h"
#include "Clock.h"

using namespace Engine::Rendering;

constexpr int Spw = 75;



void Game::GamePlay::Clock::setDisplay(Engine::Rendering::Sprite2D & display, int num)
{
	display.SetAsSpriteSet(Spw, num);
}

void Game::GamePlay::Clock::setNumDisplay(Engine::Rendering::Sprite2D & b1, Engine::Rendering::Sprite2D & b2, int num)
{
	setDisplay(b1, num % 100 / 10);
	setDisplay(b2, num % 10);
}

Game::GamePlay::Clock::Clock() :
	min1_{ NewObject<Sprite2D>("nums") },
	min2_{ NewObject<Sprite2D>("nums") },
	m1_{ NewObject<Sprite2D>("nums") },
	sec1_{ NewObject<Sprite2D>("nums") },
	sec2_{ NewObject<Sprite2D>("nums") },
	m2_{ NewObject<Sprite2D>("nums") },
	ms1_{ NewObject<Sprite2D>("nums") },
	ms2_{ NewObject<Sprite2D>("nums") }
{
	setDisplay(m1_, 10);
	setDisplay(m2_, 10);

	SetTime(0);
}

void Game::GamePlay::Clock::Update(float d)
{
	alpha_.Update(d);
	zoom_.Update(d);
	x_.Update(d);
	y_.Update(d);

	Engine::ObjectSet<Engine::Rendering::Sprite2D>::Update(d);

	min1_.SetPos(x_ - 130 * zoom_, y_);
	min2_.SetPos(x_ - 93 * zoom_, y_);
	m1_.SetPos(x_ - 56 * zoom_, y_);
	sec1_.SetPos(x_ - 18 * zoom_, y_);
	sec2_.SetPos(x_ + 18 * zoom_, y_);
	m2_.SetPos(x_ + 56 * zoom_, y_);
	ms1_.SetPos(x_ + 93 * zoom_, y_);
	ms2_.SetPos(x_ + 130 * zoom_, y_);

	min1_.SetAlpha(alpha_);
	min2_.SetAlpha(alpha_);
	m1_.SetAlpha(alpha_);
	sec1_.SetAlpha(alpha_);
	sec2_.SetAlpha(alpha_);
	m2_.SetAlpha(alpha_);
	ms1_.SetAlpha(alpha_);
	ms2_.SetAlpha(alpha_);

	min1_.SetZoom(zoom_ * 0.25f);
	min2_.SetZoom(zoom_ * 0.25f);
	m1_.SetZoom(zoom_ * 0.25f);
	sec1_.SetZoom(zoom_ * 0.25f);
	sec2_.SetZoom(zoom_ * 0.25f);
	m2_.SetZoom(zoom_ * 0.25f);
	ms1_.SetZoom(zoom_ * 0.25f);
	ms2_.SetZoom(zoom_ * 0.25f);
}

void Game::GamePlay::Clock::SetPos(float x, float y, float tween)
{
	if (tween > 0)
	{
		x_.Run(x, tween, 1);
		y_.Run(y, tween, 1);
	}
	else
	{
		x_ = x;
		y_ = y;
	}
}

void Game::GamePlay::Clock::SetZoom(float zoom, float tween)
{
	if (tween)
		zoom_.Run(zoom, tween, 1);
	else
		zoom_ = zoom;
}

void Game::GamePlay::Clock::SetTime(float sec)
{
	sec_ = sec;
	const int ms = int((sec - std::floor(sec)) * 100);
	const int se = int(std::floor(sec)) % 60;
	const int min = int(std::floor(sec)) / 60 % 100;
	
	setNumDisplay(ms1_, ms2_, ms);
	setNumDisplay(sec1_, sec2_, se);
	setNumDisplay(min1_, min2_, min);
}
