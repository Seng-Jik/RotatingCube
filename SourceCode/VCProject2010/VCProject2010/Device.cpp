#include "stdafx.h"
#include "Device.h"
#include "Optional.h"
#include "CommonClass.h"
#include "Shaders.h"
#include "Math.h"
#include "Assets.h"
using namespace Engine;
using namespace Engine::Math;

Engine::Device::Device(HWND hwnd) :
	hWnd_{ hwnd }
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
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
#ifdef _DEBUG
			D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_SINGLETHREADED,
#else
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
	
		pDxgiDevice->Release();
		pDxgiAdapter->Release();
		pDxgiFactory->Release();
	}

	// RenderTargetView
	{
		ID3D11Texture2D* backBuffer = nullptr;
		Must(SUCCEEDED(
			swapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer))));

		Must(SUCCEEDED(
			device_->CreateRenderTargetView(backBuffer,nullptr,renderTargetView_.GetAddressOf())));

		backBuffer->Release();

		auto rt = renderTargetView_.Get();


		D3D11_TEXTURE2D_DESC dsDesc;
		dsDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsDesc.Width = winRect.right - winRect.left;
		dsDesc.Height = winRect.bottom - winRect.top;
		dsDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		dsDesc.MipLevels = 1;
		dsDesc.ArraySize = 1;
		dsDesc.CPUAccessFlags = 0;
		dsDesc.SampleDesc.Count = 4;
		dsDesc.SampleDesc.Quality = x4MsaaQuality - 1;
		dsDesc.MiscFlags = 0;
		dsDesc.Usage = D3D11_USAGE_DEFAULT;
		Must(SUCCEEDED(device_->CreateTexture2D(&dsDesc, 0, zBuffer_.GetAddressOf())));
		Must(SUCCEEDED(device_->CreateDepthStencilView(zBuffer_.Get(), 0, zBufferView_.GetAddressOf())));

		auto zb = zBufferView_.Get();
		context_->OMSetRenderTargets(1, &rt, zb);
	}

	// Viewportt
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

	//Vertex Shader And Input Layout
	{
		auto buf = Engine::LoadAssets("VSDefaultWVP.cso");

		Must(SUCCEEDED(device_->CreateVertexShader(
			buf.data(),
			buf.size(),
			nullptr,
			vs_.GetAddressOf()
		)));

		context_->VSSetShader(vs_.Get(), nullptr, 0);

		const std::vector<D3D11_INPUT_ELEMENT_DESC> desc = 
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 12,D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,		0, 28,D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		Must(SUCCEEDED(device_->CreateInputLayout(desc.data(), desc.size(), buf.data(), buf.size(), inputLayout_.GetAddressOf())));
		context_->IASetInputLayout(inputLayout_.Get());

		context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	// Perspective
	{
		const auto aspect = float(winRect.right - winRect.left) / (winRect.bottom - winRect.top);
		perspective_ = DirectX::XMMatrixPerspectiveFovLH(
			DirectX::XM_PIDIV2,
			aspect,
			0.1f,
			1000.0f
		);
	}

	//Depth States
	{
		D3D11_DEPTH_STENCIL_DESC desc = CD3D11_DEPTH_STENCIL_DESC{ CD3D11_DEFAULT{} };
		desc.DepthEnable = true;
		device_->CreateDepthStencilState(&desc, depthEnable_.GetAddressOf());

		desc.DepthEnable = false;
		device_->CreateDepthStencilState(&desc, depthDisable_.GetAddressOf());

		DepthTest(false);
	}

	//Blend State
	{
		ComPtr<ID3D11BlendState> blendState;
		D3D11_BLEND_DESC d = CD3D11_BLEND_DESC{ CD3D11_DEFAULT{} };
		d.RenderTarget[0].BlendEnable = true;
		d.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		d.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
		d.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		d.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
		d.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		device_->CreateBlendState(&d, blendState.GetAddressOf());

		constexpr float t[] = { 1,1,1,1 };
		context_->OMSetBlendState(blendState.Get(),t,0xFFFFFFFF);
	}
	
}

DirectX::XMFLOAT2 Engine::Device::MouseDelta() const
{
	return std::get<1>(Mouse()) - mouseLastFrame_;
}

void Engine::Device::DepthTest(bool b)
{
	context_->OMSetDepthStencilState((b ? depthEnable_ : depthDisable_).Get(),0);
}

DirectX::XMINT2 Engine::Device::GetScreenSize() const
{
	RECT r;
	GetClientRect((HWND)hWnd_, &r);
	return DirectX::XMINT2(r.right - r.left, r.bottom - r.top);
}

float Engine::Device::GetScreenWdivH() const
{
	auto size = GetScreenSize();
	return size.x / float(size.y);
}

void Engine::Device::ResetRenderTarget()
{
	context_->OMSetRenderTargets(1, renderTargetView_.GetAddressOf(), zBufferView_.Get());
}

bool Engine::Device::EngineMainLoop()
{
	mouseLastFrame_ = std::get<1>(Mouse());

	const bool run = IsWindow((HWND)hWnd_);

	static_assert(sizeof(HWND) == sizeof(hWnd_),"HWND failed.");

	if (std::get<0>(mouse_) == MouseState::JustDown)
		std::get<0>(mouse_) = MouseState::Down;
	else if (std::get<0>(mouse_) == MouseState::JustUp)
		std::get<0>(mouse_) = MouseState::Up;

	if (run)
	{
		MSG msg;
		if (PeekMessage(&msg, (HWND)hWnd_, 0, 0, PM_REMOVE)) {

			TranslateMessage(&msg);

			if (msg.message == WM_LBUTTONDOWN)
			{
				std::get<0>(mouse_) = MouseState::JustDown;
				SetCapture((HWND)hWnd_);
			}
			else if (msg.message == WM_LBUTTONUP)
			{
				std::get<0>(mouse_) = MouseState::JustUp;
				ReleaseCapture();
			}
			else if (msg.message == WM_MOUSEMOVE)
			{
				RECT r;
				GetClientRect((HWND)hWnd_, &r);

				std::get<1>(mouse_) = DirectX::XMFLOAT2
				{
					int16_t(LOWORD(msg.lParam)) / float(r.right - r.left),
					int16_t(HIWORD(msg.lParam)) / float(r.bottom - r.top)
				};
			}
			
			DispatchMessage(&msg);



		}

		swapChain_->Present(0, 0);

		const float blue[4] = { 0,0,0,0 };
		auto& device = Engine::GetDevice();
		device.Context().ClearRenderTargetView(&device.RenderTargetView(), blue);
		device.Context().ClearDepthStencilView(&device.DepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
	}

	return run;
}

static Engine::Optional<Device> device;
Device & Engine::GetDevice()
{
	return device.Value();
}

void Engine::InitDevice(HWND hWnd)
{
	device.Emplace(hWnd);
}

