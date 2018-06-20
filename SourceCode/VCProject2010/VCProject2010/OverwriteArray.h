#pragma once
#include <array>
#include <utility>
namespace Engine
{
	template <typename T, size_t Size>
	class OverwriteArray
	{
	private:
		std::array<T,Size> arr_;
		size_t offset = 0;

	public:
		auto begin()
		{
			return arr_.begin();
		}

		auto end()
		{
			return arr_.end();
		}

		void Write(T&& d)
		{
			arr_[offset++] = std::forward<T>(d);
			if (offset >= Size) offset = 0;
		}

		size_t GetSize() const
		{
			return Size;
		}
	};
}