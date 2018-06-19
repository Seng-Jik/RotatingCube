#pragma once
#include <string>
#include "Shaders.h"
#include "VertexIn.h"
#include "GameObject.h"

namespace Engine
{
	namespace Rendering
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



			Engine::Rendering::PtrCBuffer tsf_, gscb_;
			Engine::Rendering::PtrPShader ps_;
			Engine::Rendering::PtrGShader gs_;

			float timer_ = 0;

			size_t ibSize_;

			float rotX_ = 0, rotY_ = 0, rotZ_ = 0;
			float scale_ = 1;

			DirectX::XMFLOAT3 centerOffset_ = DirectX::XMFLOAT3(0,0,0);

		public:
			ObjModel(const std::string& modelName);

			void Draw() const override;
			void Update(float) override;

			void SetRotating(DirectX::XMFLOAT3 rot);
			void SetRotating(float rotX, float rotY, float rotZ);
			void SetScale(float scale);
			void SetCenterOffset(float x,float y,float z);
		};
	}
}