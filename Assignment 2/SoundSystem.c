#include "SoundSystem.h"
#include <stdio.h>

const char* SOUND_FILENAMES[] = 
{
	L"./sfx/bgm.wav",
	L"./sfx/explode.wav",
	L"./sfx/missile.wav",
	L"./sfx/scarymonsternicespritemidi.wav"
};

void play_sound(SoundType t)
{
	PlaySound(SOUND_FILENAMES[t], NULL, SND_FILENAME | SND_ASYNC);
}