#pragma once
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
	};
}