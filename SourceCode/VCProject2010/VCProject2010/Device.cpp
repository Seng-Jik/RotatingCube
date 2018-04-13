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
		scDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;          //�̶�����  
		scDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;  //�̶�����  
		scDesc.BufferCount = 1;                 //����������  
		scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;       //UsageΪRender Target Output  
		scDesc.Flags = 0;
		scDesc.OutputWindow = hwnd;           //�����ھ��  
		scDesc.SampleDesc.Count = 4;            //4��������  
		scDesc.SampleDesc.Quality = x4MsaaQuality - 1;    //4�ز���֧�ֵȼ�  
		scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;   //���ò���  
		scDesc.Windowed = true;             //����ģʽ  
	}
}

Engine::Rendering::Device::~Device()
{
}
