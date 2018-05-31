#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl/client.h>

namespace Engine
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

		ComPtr<ID3D11Texture2D> zBuffer_;
		ComPtr<ID3D11DepthStencilView> zBufferView_;
		ComPtr<ID3D11InputLayout> inputLayout_;

		DirectX::XMMATRIX perspective_;

		const void* hWnd_;

		std::tuple<bool, DirectX::XMFLOAT2> mouse_;
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

		inline auto& DepthStencilView()
		{
			return *zBufferView_.Get();
		}

		inline auto& D3DDevice()
		{
			return *device_.Get();
		}

		inline auto& Context()
		{
			return *context_.Get();
		}

		inline auto Mouse() const
		{
			return mouse_;
		}

		DirectX::XMINT2 GetScreenSize() const;
		float GetScreenWdivH() const;

		bool EngineMainLoop();
	};

	Device& GetDevice();
	void InitDevice(HWND hWnd);

}