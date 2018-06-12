#include "stdafx.h"
#include "ObjLoader.h"
#include "Assets.h"
#include <sstream>

using namespace Engine::Rendering;
std::tuple<VecVertex, VecIndicis> Engine::Rendering::LoadObjModel(const std::string & assetPath)
{
	auto obj = Engine::LoadAssets(assetPath + ".obj");
	obj.push_back('\0');

	std::stringstream objss(obj.data());

	VecVertex vertexComponent;
	VecIndicis indicisComponent;

	while (!objss.eof())
	{
		std::string line;
		std::getline(objss,line);

		std::stringstream liness(line);
		
		std::string command;
		std::string args[3];

		liness >> command;
		if (command == "v")
		{
			VertexIn vtx;
			liness >> vtx.position.x;
			liness >> vtx.position.y;
			liness >> vtx.position.z;
			vtx.color = DirectX::XMFLOAT4(1, 1, 1, 1);
			vtx.texCoord = DirectX::XMFLOAT2(1, 1);
			vertexComponent.push_back(vtx);
		}

		else if (command == "f")
		{
			size_t a, b, c;
			liness >> a;
			liness >> b;
			liness >> c;
			indicisComponent.push_back(a - 1);
			indicisComponent.push_back(b - 1);
			indicisComponent.push_back(c - 1);
		}
	}
	
	return std::make_tuple(std::move(vertexComponent), std::move(indicisComponent));
}
