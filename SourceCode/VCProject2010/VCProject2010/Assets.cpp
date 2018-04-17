#include "stdafx.h"
#include "Assets.h"
#include <fstream>

std::vector<char> Engine::LoadAssets(const std::string & name)
{
	std::ifstream in(name.c_str(), std::ios::binary);

	Must(in.good());

	in.seekg(0, std::ios::end);
	const std::size_t size = std::size_t(in.tellg());
	in.seekg(0, std::ios::beg);

	std::vector<char> ret;
	ret.resize(size);
	
	in.read(ret.data(), size);

	in.close();

	return ret;
}
