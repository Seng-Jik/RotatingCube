#pragma once
#include <exception>

namespace Engine
{
	inline void Must(bool b)
	{
		if (!b) std::terminate();
	}
}
