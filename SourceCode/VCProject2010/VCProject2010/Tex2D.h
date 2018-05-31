#pragma once
#include "Device.h"

namespace Engine
{
	namespace Rendering
	{
		using PtrTex2D = ComPtr<ID3D11Texture2D>;

		PtrTex2D LoadTex2D(const char* texName);
	}
}