#pragma once
#include <DirectXMath.h>
#include <vector>
#include <tuple>
namespace Engine
{
	namespace Renderer
	{
		using VecVertex = std::vector<DirectX::XMFLOAT4>;
		using VecIndicis = std::vector<size_t>;

		std::tuple<VecVertex, VecIndicis> LoadObjModel(const std::string& assetPath);
	}
}