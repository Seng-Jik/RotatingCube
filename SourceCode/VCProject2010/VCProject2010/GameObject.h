#pragma once

namespace Engine
{
	class GameObject
	{
	public:
		GameObject() = default;
		GameObject(const GameObject&) = delete;

		virtual ~GameObject(){}
		virtual void Update(float deltaTime){}
		virtual void Draw() const{}
		virtual bool Live() const { return true; }

	};
}