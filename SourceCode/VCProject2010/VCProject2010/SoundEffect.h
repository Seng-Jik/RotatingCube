#pragma once

namespace Game
{
	namespace SoundEffect
	{
		enum class SoundEffect : int
		{
			Pluck = 0,
			Entry = 1
		};

		void Init();
		void Play(SoundEffect);
		void Quit();
	}
}
