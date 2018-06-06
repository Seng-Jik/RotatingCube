#include "stdafx.h"
#include "ObjLoader.h"
#include "Assets.h"
#include <sstream>

using namespace Engine::Renderer;
std::tuple<VecVertex, VecIndicis> Engine::Renderer::LoadObjModel(const std::string & assetPath)
{
	auto obj = Engine::LoadAssets(assetPath);
	obj.push_back('\0');

	std::stringstream objss(obj.data());

	VecVertex vertexComponent;
	VecIndicis indicisComponent;

	while (!objss.eof())
	{
		std::string line;
		std::getline(objss,line);

		std::stringstream liness;
		
		std::string command;
		std::string args[3];

		liness >> command;
		if (command == "v")
		{
			DirectX::XMFLOAT3 vtx;
			liness >> vtx.x;
			liness >> vtx.y;
			liness >> vtx.z;
		}

		else if (command == "f")
		{

		}
	}
	
	throw std::exception("No impl!");
}
