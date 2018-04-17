#pragma once
#include <string>
#include <wrl/client.h>
#include "../FX11/inc/d3dx11effect.h"

namespace Engine
{
	using Microsoft::WRL::ComPtr;

	namespace Rendering
	{
		class Effect
		{
		private:
			ComPtr<ID3DX11Effect> effect_;
		public:

			Effect(const std::wstring& effectName);
			Effect(const Effect&) = delete;
		};
	}
}