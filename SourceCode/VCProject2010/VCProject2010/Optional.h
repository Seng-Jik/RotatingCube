#pragma once

namespace Engine
{
	template <typename T>
	class Optional
	{
	private:
		char mem_[sizeof(T)];
		T* obj_ = nullptr;

	public:
		Optional() = default;
		Optional(const Optional<T>&) = delete;


		template <typename ...TArgs>
		void Emplace(TArgs&&... arg)
		{
			obj_ = new(mem_) T(std::forward<TArgs>(arg)...);
		}

		void Clear() 
		{
			if (obj_ != nullptr)
				obj_->~T();
			obj_ = nullptr;
		}

		bool Exist() const 
		{
			return obj != nullptr;
		}

		T& Value() 
		{ 
			return *obj_;
		}

		~Optional()
		{
			Clear();
		}

		T* operator ->()
		{
			return obj_;
		}
	};
}