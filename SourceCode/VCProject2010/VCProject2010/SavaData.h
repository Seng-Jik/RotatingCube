#pragma once
#include <bitset>
#include "StageData.h"
namespace Game
{
	class SaveData
	{
	private:
		SaveData();
		SaveData(const SaveData&) = delete;
		SaveData& operator = (const SaveData&) = delete;

		std::bitset<8> stageOpened_;
		std::array<float, 8> stageTime_;

		void flush();

	public:
		static SaveData& Get();

		bool StageOpened(int stage) const;
		float GetStageTime(GamePlay::StageName stgName) const;
		void OpenStage(GamePlay::StageName stgName);
		void WriteTime(GamePlay::StageName stgName,float time);
	};
}