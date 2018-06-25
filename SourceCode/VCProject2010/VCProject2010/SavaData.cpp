#include "stdafx.h"
#include "SavaData.h"

using namespace Game;

Game::SaveData::SaveData()
{
}

SaveData & Game::SaveData::Get()
{
	static SaveData sv;
	return sv;
}

bool Game::SaveData::StageOpened(int stage) const
{
	if (stage == 1 || stage == 2 || stage == 3)
		return true;
	return false;
}

float Game::SaveData::GetStageTime(GamePlay::StageName stgName)
{
	return 2333.0f;
}

void Game::SaveData::OpenStage(GamePlay::StageName stgName)
{
	Engine::Log("OpenStage", stgName);
}

void Game::SaveData::WriteTime(GamePlay::StageName stgName,float time)
{
	Engine::Log("WriteTime", stgName, time);
}



