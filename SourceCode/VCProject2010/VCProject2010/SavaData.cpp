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

