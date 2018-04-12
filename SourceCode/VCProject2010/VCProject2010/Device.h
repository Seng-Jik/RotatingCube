#pragma once
#include <d3d11.h>
#include <wrl/client.h>

namespace Engine
{
	using Microsoft::WRL::ComPtr;

	namespace Rendering
	{
		class Device
		{
		private:
			ComPtr<ID3D11Device> device_;
			ComPtr<ID3D11DeviceContext> context_;
			ComPtr<IDXGISwapChain> swapChain_;

		public:
			Device(HWND hwnd);
			~Device();

			Device(const Device&) = delete;
		};
	}
}