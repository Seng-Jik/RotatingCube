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
			ComPtr<ID3D11RenderTargetView> renderTargetView_;
		public:
			Device(HWND hwnd);

			Device(const Device&) = delete;

			inline auto& RenderTargetView()
			{
				return *renderTargetView_.Get();
			}

			inline auto& D3DDevice()
			{
				return *device_.Get();
			}

			inline auto& Context()
			{
				return *context_.Get();
			}

			bool EngineMainLoop(HWND hWnd);
		};

		Device& GetDevice();
		void InitDevice(HWND hWnd);
	}
}