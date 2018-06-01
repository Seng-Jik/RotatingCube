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

		using PtrVBuffer = ComPtr<ID3D11Buffer>;
		struct VertexIn
		{
			DirectX::XMFLOAT3 position;
			DirectX::XMFLOAT4 color;
			DirectX::XMFLOAT2 texCoord;

			static PtrVBuffer CreateVBuffer(const std::vector<VertexIn>& vtx);
			static PtrVBuffer CreateVBuffer(const VertexIn* vtx,size_t size);

			template <size_t Size>
			static PtrVBuffer CreateVBuffer(const std::array<VertexIn, Size>& vtx)
			{
				return CreateVBuffer(vtx.data(), Size);
			}

			static void UpdateVBuffer(const PtrVBuffer& vb, const VertexIn* vin);
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


		using PtrCBuffer = ComPtr<ID3D11Buffer>;
		template <typename TPODStruct>
		PtrCBuffer CreateConstantBuffer(const TPODStruct& data)
		{
			PtrCBuffer ret;

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
		void UpdateCBuffer(const PtrCBuffer& dst, const TPODStruct& src)
		{
			GetDevice().Context().UpdateSubresource(dst.Get(), 0, nullptr, &src, 0, 0);
		}
	}
}