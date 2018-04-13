#include "stdafx.h"
#include "Device.h"
#include "Globals.h"

Engine::Rendering::Device::Device(HWND hwnd)
{
	UINT x4MsaaQuality;
	RECT winRect;
	GetClientRect(hwnd, &winRect);

	// Device
	{
		std::array<D3D_FEATURE_LEVEL, 6> featureLevels =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};

		D3D_FEATURE_LEVEL currentLevel;

		const auto result = D3D11CreateDevice(
			nullptr,
#ifdef _DEBUG
			D3D_DRIVER_TYPE_REFERENCE,
			nullptr,
			D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_SINGLETHREADED,
#else
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			D3D11_CREATE_DEVICE_SINGLETHREADED,
#endif
			featureLevels.data(),
			featureLevels.size(),
			D3D11_SDK_VERSION,
			device_.GetAddressOf(),
			&currentLevel,
			context_.GetAddressOf()
		);

		Must(SUCCEEDED(result));

		Must(SUCCEEDED(
			device_->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &x4MsaaQuality)));
	}

	// SwapChain
	{
		DXGI_SWAP_CHAIN_DESC scDesc{ 0 };
		scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scDesc.BufferDesc.Height = winRect.bottom - winRect.top;
		scDesc.BufferDesc.Width = winRect.right - winRect.left;
		scDesc.BufferDesc.RefreshRate.Numerator = 60;
		scDesc.BufferDesc.RefreshRate.Denominator = 1;
		scDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		scDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		scDesc.BufferCount = 1;
		scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scDesc.Flags = 0;
		scDesc.OutputWindow = hwnd;
		scDesc.SampleDesc.Count = 4;
		scDesc.SampleDesc.Quality = x4MsaaQuality - 1;
		scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		scDesc.Windowed = true;

		IDXGIDevice *pDxgiDevice = nullptr;
		Must(SUCCEEDED(device_.Get()->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&pDxgiDevice))));
		IDXGIAdapter *pDxgiAdapter = nullptr;
		Must(SUCCEEDED(pDxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&pDxgiAdapter))));
		IDXGIFactory *pDxgiFactory = nullptr;
		Must(SUCCEEDED(pDxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pDxgiFactory))));
		Must(SUCCEEDED(pDxgiFactory->CreateSwapChain(device_.Get(), &scDesc, swapChain_.GetAddressOf())));
	}

	// RenderTargetView
	{
		ID3D11Texture2D* backBuffer = nullptr;
		Must(SUCCEEDED(
			swapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer))));

		Must(SUCCEEDED(
			device_->CreateRenderTargetView(backBuffer,nullptr,renderTargetView_.GetAddressOf())));

		backBuffer->Release();
	}

	// Viewport
	{
		D3D11_VIEWPORT v
		{
			0.0f,
			0.0f,
			float(winRect.right - winRect.left),
			float(winRect.bottom - winRect.top),
			0.0f,
			1.0f
		};

		context_->RSSetViewports(1,&v);
	}
}

bool Engine::Rendering::Device::EngineMainLoop(HWND hWnd)
{

	MSG msg;
	if (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE)) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (msg.message == WM_DESTROY)
			return false;
	}

	const float color[4] = { 1,0,0,1 };
	Context().ClearRenderTargetView(&RenderTargetView(), color);

	swapChain_->Present(0, 0);

	return true;
}
