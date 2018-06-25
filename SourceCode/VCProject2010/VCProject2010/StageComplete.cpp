#include "stdafx.h"
#include "StageComplete.h"
#include "Button.h"

Game::GamePlay::StageComplete::StageComplete(Engine::ObjectSet<>* mainBk, std::function<void()> gameMainExit):
	finishHint_{ NewObject<Engine::Rendering::Sprite2D>("finish") }
{
	hintProgress_.Run(1, 3, 1);

	auto& back = NewObject<Engine::Button>("list");
	auto& rest = NewObject<Engine::Button>("restart");
	auto& next = NewObject<Engine::Button>("next");

	back.PosX() = -100;
	next.PosX() = 100;

	back.PosY() = next.PosY() = rest.PosY() = -150;

	back.Alpha() = 0;
	rest.Alpha() = 0;
	next.Alpha() = 0;

	back.Zoom() = 0.95f;
	rest.Zoom() = 0.95f;
	next.Zoom() = 0.95f;

	tl_.AddTask([&] {

		tl_.AddTask([&back] {
			back.Zoom().Run(0.5f, 0.2f, 1);
			back.Alpha().Run(1, 0.2f, 1);
		}, 0.25f);

		tl_.AddTask([&rest] {
			rest.Zoom().Run(0.5f, 0.2f, 1);
			rest.Alpha().Run(1, 0.2f, 1);
		}, 0.45f);

		tl_.AddTask([&next] {
			next.Zoom().Run(0.5f, 0.2f, 1);
			next.Alpha().Run(1, 0.2f, 1);
		}, 0.65f);

		tl_.AddTask([&] {
			rest.SetEnable(true);
			back.SetEnable(true);
			next.SetEnable(true);
		},0.85f);
	},3);
}

void Game::GamePlay::StageComplete::Update(float d)
{
	tl_.Update(d);
	hintProgress_.Update(d);
	finishHint_.SetAlpha(hintProgress_);
	finishHint_.SetZoom(2 - 1.5f*hintProgress_);
	finishHint_.SetPos(0, 100 * hintProgress_);
	Engine::ObjectSet<>::Update(d);
}
