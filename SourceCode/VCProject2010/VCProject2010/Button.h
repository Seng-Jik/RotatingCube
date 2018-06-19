#pragma once
#include "Sprite2D.h"
#include "Tween.h"
#include <functional>

namespace Engine
{
	class Button : public Rendering::Sprite2D
	{
	private:
		Tween<float> posX_ = 0, posY_ = 0, alpha_ = 1, zoom_ = 1;

		bool lastMode = false;
		MouseState lastMouseDown = MouseState::Up;
		bool clickEnabled_ = false;
		std::function<void()> onClick_;

		bool activeEnabled_ = true;
	public:
		using Sprite2D::Sprite2D;

		auto& Alpha()
		{
			return alpha_;
		}

		auto& Zoom()
		{
			return zoom_;
		}

		auto& PosX()
		{
			return posX_;
		}

		auto& PosY()
		{
			return posY_;
		}

		void SetOnClick(const std::function<void()>& onClick);

		void Update(float time) override;

		void SetEnable(bool b);

		void DisableActive();
	};
}
