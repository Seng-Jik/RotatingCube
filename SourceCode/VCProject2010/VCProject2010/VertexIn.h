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

		struct Transform
		{
			DirectX::XMMATRIX world;
			DirectX::XMMATRIX view;
			DirectX::XMMATRIX prj;

			Transform Transpose() const
			{
				return{
					DirectX::XMMatrixTranspose(world),
					DirectX::XMMatrixTranspose(view),
					DirectX::XMMatrixTranspose(prj)
				};
			}
		};


		template <typename TPODStruct>
		ComPtr<ID3D11Buffer> CreateConstantBuffer(const TPODStruct& data)
		{
			ComPtr<ID3D11Buffer> ret;

			D3D11_BUFFER_DESC desc{ 0 };
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.ByteWidth = sizeof(TPODStruct);
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA initData{ 0 };
			initData.pSysMem = &data;
			Must(SUCCEEDED(GetDevice().D3DDevice().CreateBuffer(&desc, &initData, ret.GetAddressOf())));

			return ret;
		}

		template <typename TPODStruct>
		void UpdateBuffer(const ComPtr<ID3D11Buffer>& dst, const TPODStruct& src)
		{
			GetDevice().Context().UpdateSubresource(dst.Get(), 0, nullptr, &src, 0, 0);
		}
	}
}