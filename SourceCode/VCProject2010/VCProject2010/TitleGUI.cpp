#include "stdafx.h"
#include "TitleGUI.h"
#include "SoundEffect.h"

using namespace Engine::Rendering;

Game::Title::TitleGUI::TitleGUI() :
	logo_ { NewObject<Sprite2D>("cube") },
	hint_ { NewObject<Sprite2D>("titlehint")},
	about_{ NewObject<Sprite2D>("about") }
{
	logoAnimationTween_ = 0;
	logoAnimationTween_.Run(1, 2, 2);

	hintAlphaMul_ = 0;
	tl_.AddTask([this] {
		hintAlphaMul_.Run(1, 0.5f, 1);
	}, 2);

	hint_.SetZoom(0.5f);
	hint_.SetPos(0, -100);

	about_.SetPos(0, -240);
	about_.SetZoom(0.6f);
}

void Game::Title::TitleGUI::Update(float time)
{
	timer_ += time;
	hintAlphaMul_.Update(time);
	hint_.SetAlpha(hintAlphaMul_ * (sinf(timer_ * 3) * 0.25f + 0.75f));


	about_.SetAlpha(hintAlphaMul_ * 0.5f);

	tl_.Update(time);
	logoAnimationTween_.Update(time);
	logo_.SetAlpha(logoAnimationTween_);
	logo_.SetZoom(1 - (logoAnimationTween_ * 0.75f));
	logo_.SetPos(0,100* logoAnimationTween_);
	Engine::ObjectSet<Engine::Rendering::Sprite2D>::Update(time);
}

void Game::Title::TitleGUI::Click()
{
	logoAnimationTween_.Run(0, 0.5f, 1);
	hintAlphaMul_.Run(0, 0.1f, 1);
	tl_.AddTask([this] { Kill(); }, 0.5f);

	SoundEffect::Play(SoundEffect::SoundEffect::Entry);
}

