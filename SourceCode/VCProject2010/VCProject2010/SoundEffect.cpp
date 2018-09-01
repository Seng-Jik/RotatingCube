#include "stdafx.h"
#include "SoundEffect.h"
#include <SDL_mixer.h>

static Mix_Chunk* soundEffects[2] = { nullptr };

void Game::SoundEffect::Init()
{
	soundEffects[int(SoundEffect::Pluck)] = Mix_LoadWAV("Pluck.ogg");
	soundEffects[int(SoundEffect::Entry)] = Mix_LoadWAV("Entry.ogg");
}

void Game::SoundEffect::Play(SoundEffect s)
{
	Mix_PlayChannel(-1, soundEffects[int(s)], 0);
}

void Game::SoundEffect::Quit()
{
	for (auto p : soundEffects)
		if (p)
			Mix_FreeChunk(p);
}
