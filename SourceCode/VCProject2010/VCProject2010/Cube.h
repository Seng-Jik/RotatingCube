#pragma once
#include "VertexIn.h"
#include "GameObject.h"

namespace Game
{
	namespace EngineTests
	{
		class Cube : public Engine::GameObject
		{
		private:
			Engine::Rendering::ComPtr<ID3D11Buffer> buf_;
			Engine::Rendering::ComPtr<ID3D11PixelShader> ps_;
		public:
			Cube();
			void Update(float) override;
			void Draw() const override;
		};
	}
}