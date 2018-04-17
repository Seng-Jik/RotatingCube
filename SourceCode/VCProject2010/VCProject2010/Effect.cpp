#include "stdafx.h"
#include "Effect.h"
#include <fstream>
#include "Globals.h"
#include "Device.h"
#include <D3DCompiler.h>

Engine::Rendering::Effect::Effect(const std::wstring & effectName)
{	
	ComPtr<ID3DBlob> error;

	constexpr UINT compileFlags =
#ifdef _DEBUG
		D3DCOMPILE_DEBUG;
#else
		D3DCOMPILE_OPTIMIZATION_LEVEL3;
#endif

	Must(SUCCEEDED(D3DX11CompileEffectFromFile(
		(effectName + L".fx").c_str(),
		nullptr,
		nullptr,
		compileFlags,
		0,
		&GetDevice().D3DDevice(),
		effect_.GetAddressOf(),
		error.GetAddressOf())));

	if (error.Get())
	{
		OutputDebugString(LPCSTR(error->GetBufferPointer()));
	}
}
