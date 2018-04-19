#pragma once
#include "VertexIn.h"
#include "GameObject.h"

namespace Game
{
	namespace EngineTests
	{
		class DemoCube : public Engine::GameObject
		{
		private:
			Engine::Rendering::ComPtr<ID3D11Buffer> vb_;
			std::size_t vbSize_;
			Engine::Rendering::ComPtr<ID3D11PixelShader> ps_;

			Engine::Rendering::ComPtr<ID3D11Buffer> constBuffer_;

			Engine::Rendering::Transform buildTransform(const DirectX::XMMATRIX& world);

		public:
			DemoCube();
			void Update(float) override;
			void Draw() const override;

			void SetRotation(float x, float y, float z);
		};
	}
}