#pragma once
#include <Windows.h>

typedef enum _stype
{
	SOUND_BGM = 0,
	SOUND_EXPLODE = 1,
	SOUND_MISSILE = 2,
	SOUND_MIDI = 3
} SoundType;

void play_sound(SoundType t);