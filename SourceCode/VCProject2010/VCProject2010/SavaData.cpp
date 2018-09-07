#include "stdafx.h"
#include "SavaData.h"
#include "StageData.h"
#include <fstream>

using namespace Game;

Game::SaveData::SaveData()
{
	stageOpened_.reset();
	stageOpened_.set(GamePlay::Stage1);
	stageTime_.fill(-1);

	std::ifstream in("save.sav", std::ios::binary);
	if (in.good())
	{
		unsigned long long so;
		in.read((char*)&so, sizeof(so));
		stageOpened_ = std::bitset<8>(so);
		in.read((char*)stageTime_.data(), sizeof(float)*8);
		in.close();
	}
}

void Game::SaveData::flush()
{
	std::ofstream out("save.sav", std::ios::binary);
	Engine::Must(out.good());

	const unsigned long long so = stageOpened_.to_ullong();
	out.write((char*)&so, sizeof(so));
	out.write((char*)stageTime_.data(), sizeof(float)*8);
	out.close();
}

SaveData & Game::SaveData::Get()
{
	static SaveData sv;
	return sv;
}

bool Game::SaveData::StageOpened(int stage) const
{
	return stageOpened_.test(stage);
}

float Game::SaveData::GetStageTime(GamePlay::StageName stgName) const
{
	return stageTime_[stgName];
}

void Game::SaveData::OpenStage(GamePlay::StageName stgName)
{
	if (stgName != GamePlay::None)
	{
		stageOpened_.set(stgName);
		flush();
	}
}

void Game::SaveData::WriteTime(GamePlay::StageName stgName, float time)
{
	if (time < stageTime_[stgName] || stageTime_[stgName] < 0)
	{
		stageTime_[stgName] = time;
		flush();
	}

}



