#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl/client.h>

namespace Engine
{
	namespace Rendering
	{
		using Microsoft::WRL::ComPtr;

		class Device
		{
		private:
			ComPtr<ID3D11Device> device_;
			ComPtr<ID3D11DeviceContext> context_;
			ComPtr<IDXGISwapChain> swapChain_;
			ComPtr<ID3D11RenderTargetView> renderTargetView_;
			ComPtr<ID3D11VertexShader> vs_;

			ComPtr<ID3D11InputLayout> inputLayout_;

			DirectX::XMMATRIX perspective_;
		public:
			Device(HWND hwnd);

			Device(const Device&) = delete;

			auto Perspective()
			{
				return perspective_;
			}

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