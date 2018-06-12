#pragma once
#include <DirectXMath.h>
#include <vector>
#include <tuple>
#include "VertexIn.h"
namespace Engine
{
	namespace Rendering
	{
		using VecVertex = std::vector<Rendering::VertexIn>;
		using VecIndicis = std::vector<size_t>;

		std::tuple<VecVertex, VecIndicis> LoadObjModel(const std::string& assetPath);
	}
}