#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl/client.h>
#include <vector>

namespace Engine
{
	namespace Rendering
	{
		using Microsoft::WRL::ComPtr;

		struct VertexIn
		{
			DirectX::XMFLOAT3 position;
			DirectX::XMFLOAT4 color;
			DirectX::XMFLOAT2 texCoord;

			static ComPtr<ID3D11Buffer> CreateBuffer(const std::vector<VertexIn>& vtx);
		};
	}
}