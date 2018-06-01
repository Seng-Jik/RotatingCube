#pragma once
#include "Tween.h"
#include "Sprite2D.h"

namespace Engine
{
	class Cursor : public Rendering::Sprite2D
	{
	private:
		Tween<float> alpha_;
	public:
		Cursor();

		void Show();
		void Hide();
		void Update(float time);
	};
}