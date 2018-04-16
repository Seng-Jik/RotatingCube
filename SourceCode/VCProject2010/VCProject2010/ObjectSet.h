#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"

namespace Engine
{
	template <typename ObjectType>
	class ObjectSet : public GameObject
	{
	private:
		std::vector<std::unique_ptr<ObjectType>> objects_;
		bool live_ = true;

	public:
		virtual void Update(float deltaTime)
		{
			for (auto& p : objects_)
				p->Update(deltaTime);
		}

		virtual void Draw() const 
		{
			for (const auto& p : objects_)
				p->Draw();
		}

		virtual bool Live() const 
		{ 
			return live_; 
		}

		template <typename T,typename ...TArgs>
		T& NewObject(TArgs&&... args)
		{
			auto pObj = new T(std::forward<TArgs>(args)...);
			objects_.push_back(std::unique_ptr<ObjectType>(pObj));
			return *pObj;
		}

		void Kill()
		{
			live_ = false;
		}
	};
}
