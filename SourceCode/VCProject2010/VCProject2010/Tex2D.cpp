#include "stdafx.h"
#include "Tex2D.h"
#include <fstream>

using namespace Engine::Rendering;

PtrTex2D Engine::Rendering::LoadTex2D(const char * texName)
{
	std::ifstream in(texName + std::string(".sst"), std::ios::binary);

	in.get();	//Compress Mode

	uint16_t rectSize;
	in.read((char*)&rectSize, sizeof(rectSize));

	uint16_t w, h;
	in.read((char*)&w, sizeof(w));
	in.read((char*)&h, sizeof(h));

	uint16_t ignore[4];
	for (uint16_t i = 0; i < rectSize; ++i)
		in.read((char*)ignore, sizeof(ignore));

	int32_t dataSize;
	in.read((char*)&dataSize, sizeof(dataSize));

	std::vector<unsigned char> pixels;
	pixels.resize(dataSize);
	in.read((char*)pixels.data(), pixels.size());
}
