#include "stdafx.h"
#include "Device.h"
#include "Globals.h"

Engine::Rendering::Device::Device(HWND hwnd)
{
	UINT x4MsaaQuality;
	//=========================================================Device
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

	//=========================================================SwapChain
	{
		DXGI_SWAP_CHAIN_DESC scDesc{ 0 };
		scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scDesc.BufferDesc.Width = 640;
		scDesc.BufferDesc.Height = 480;
		scDesc.BufferDesc.RefreshRate.Numerator = 60;
		scDesc.BufferDesc.RefreshRate.Denominator = 1;
		scDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;          //固定参数  
		scDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;  //固定参数  
		scDesc.BufferCount = 1;                 //缓冲区个数  
		scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;       //Usage为Render Target Output  
		scDesc.Flags = 0;
		scDesc.OutputWindow = hwnd;           //主窗口句柄  
		scDesc.SampleDesc.Count = 4;            //4个采样点  
		scDesc.SampleDesc.Quality = x4MsaaQuality - 1;    //4重采样支持等级  
		scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;   //常用参数  
		scDesc.Windowed = true;             //窗口模式  
	}
}

Engine::Rendering::Device::~Device()
{
}
