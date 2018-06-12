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
		Engine::Rendering::PtrVBuffer vbo_;
		Engine::Rendering::PtrVBuffer ibo_;

		Engine::Rendering::Transform tsfcpu_;
		Engine::Rendering::PtrCBuffer tsf_;

		Engine::Rendering::PtrPShader ps_;

		size_t ibSize_;

	public:
		ObjModel(const std::string& modelName);

		void Draw() const override;
		void Update(float) override;

	};
}