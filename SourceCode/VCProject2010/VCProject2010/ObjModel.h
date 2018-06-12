#pragma once
#include <string>
#include "Shaders.h"
#include "VertexIn.h"
#include "GameObject.h"

namespace Game
{
	class ObjModel : public Engine::GameObject
	{
	private:
		
		struct GSCB
		{
			DirectX::XMVECTOR eyepos;
		};

		Engine::Rendering::PtrVBuffer vbo_;
		Engine::Rendering::PtrVBuffer ibo_;

		
		
		Engine::Rendering::PtrCBuffer tsf_,gscb_;
		Engine::Rendering::PtrPShader ps_;
		Engine::Rendering::PtrGShader gs_;

		float timer_ = 0;

		size_t ibSize_;

	public:
		ObjModel(const std::string& modelName);

		void Draw() const override;
		void Update(float) override;

	};
}