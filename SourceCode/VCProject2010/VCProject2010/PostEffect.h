#pragma once
#include "VertexIn.h"

namespace Engine
{
	namespace Rendering
	{
		class PostEffect
		{
		private:
			ComPtr<ID3D11PixelShader> peps_;
			ComPtr<ID3D11Buffer> pscb_;

			static std::tuple<PtrCBuffer,PtrVBuffer> getVSBuffers();
			
		public:
			PostEffect(const char* peps);
			PostEffect(const PostEffect&) = delete;
			const PostEffect& operator =(const PostEffect&) = delete;

			void SetConstantBuffer(const ComPtr<ID3D11Buffer>&);
			void Draw() const;
		};
	}
}