#include "stdafx.h"
#include "Device.h"

Engine::Rendering::Device::Device(HWND hwnd)
{
	//=========================================================Device
	std::array<D3D_FEATURE_LEVEL,6> featureLevels = 
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1 
	};

	D3D_FEATURE_LEVEL currentLevel;

	D3D11CreateDevice(
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

	if (device_.Get() == nullptr) std::terminate();
	if (context_.Get() == nullptr) std::terminate();

	//=========================================================SwapChain
	DXGI_SWAP_CHAIN_DESC swapChainDesc{ 0 };

	/*
	https://blog.csdn.net/bonchoix/article/details/8288868
	*/
}

Engine::Rendering::Device::~Device()
{
}
