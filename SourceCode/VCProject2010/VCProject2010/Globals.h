#pragma once
#include <exception>
#include <iostream>
#include <utility>
namespace Engine
{
	inline void Must(bool b)
	{
		if (!b) std::terminate();
	}

	void ShowCursor(bool b);

	namespace LogImpl
	{
		template<typename T>
		void Log(T&& arg)
		{
			std::cout << std::forward<T>(arg);
		}

		template <typename T, typename ...TArgs>
		void Log(T&& arg, TArgs&&... args)
		{
			Log(std::forward<T>(arg));
			std::cout << ',';
			Log(std::forward<TArgs>(args)...);
		}
	}
	
	template<typename ...T>
	void Log(T&&... args)
	{
		LogImpl::Log(std::forward<T>(args)...);
		std::cout << std::endl;
	}
}
