#pragma once
#include "StageData.h"
namespace Game
{
	class SaveData
	{
	private:
		SaveData();
		SaveData(const SaveData&) = delete;
		SaveData& operator = (const SaveData&) = delete;

	public:
		static SaveData& Get();

		bool StageOpened(int stage) const;
		float GetStageTime(GamePlay::StageName stgName);
		void OpenStage(GamePlay::StageName stgName,float time) const;
	};
}