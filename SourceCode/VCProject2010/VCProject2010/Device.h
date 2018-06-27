#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl/client.h>

namespace Engine
{
	using Microsoft::WRL::ComPtr;

	enum class MouseState
	{
		JustDown,
		Down,
		JustUp,
		Up
	};

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

		std::tuple<MouseState, DirectX::XMFLOAT2> mouse_ = std::make_tuple(MouseState::Up,DirectX::XMFLOAT2(0,0));
		DirectX::XMFLOAT2 mouseLastFrame_ = DirectX::XMFLOAT2(0, 0);

		ComPtr<ID3D11DepthStencilState> depthEnable_, depthDisable_;
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

		DirectX::XMFLOAT2 MouseDelta() const;

		void DepthTest(bool);

		DirectX::XMINT2 GetScreenSize() const;
		float GetScreenWdivH() const;

		void ResetRenderTarget();

		bool KeyDown(int keyName) const;

		bool EngineMainLoop();
	};

	Device& GetDevice();
	void InitDevice(HWND hWnd);

}