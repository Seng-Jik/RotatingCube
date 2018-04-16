#pragma once

namespace Engine
{
	class GameObject
	{
	public:
		virtual ~GameObject(){}
		virtual void Update(float deltaTime){}
		virtual void Draw() const{}
		virtual bool Live() const { return true; }

	};
}