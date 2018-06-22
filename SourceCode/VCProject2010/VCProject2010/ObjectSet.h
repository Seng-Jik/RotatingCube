#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"

namespace Engine
{
	template <typename ObjectType = GameObject>
	class ObjectSet : public GameObject
	{
	private:
		std::vector<std::unique_ptr<ObjectType>> objects_;
		std::stack<std::unique_ptr<ObjectType>> newObjs_;
		bool live_ = true;

	public:
		virtual void Update(float deltaTime)
		{
			while (!newObjs_.empty())
			{
				objects_.push_back(std::move(newObjs_.top()));
				newObjs_.pop();
			}
			for (auto& p : objects_)
				p->Update(deltaTime);

			const auto nend = std::remove_if(objects_.begin(),objects_.end(),
				[](const auto& obj) {
				return !obj->Live();
			});

			objects_.erase(nend, objects_.end());
		}

		virtual void Draw() const 
		{
			static std::stack<ObjectType*> onTop;
			for (const auto& p : objects_)
			{
				if (p->DrawOnTop)
					onTop.push(p.get());
				else
					p->Draw();
			}

			while (!onTop.empty())
			{
				onTop.top()->Draw();
				onTop.pop();
			}
		}

		virtual bool Live() const 
		{ 
			return live_; 
		}

		template <typename T,typename ...TArgs>
		T& NewObject(TArgs&&... args)
		{
			auto pObj = new T(std::forward<TArgs>(args)...);
			newObjs_.emplace(std::unique_ptr<ObjectType>(pObj));
			return *pObj;
		}

		void Kill()
		{
			live_ = false;
		}
	};
}
