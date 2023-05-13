#include "SoundSystem.h"
#include <stdio.h>

// don't actually use this. just type the fucking string in
const char* SOUND_FILENAMES[] = 
{
	"./sfx/bgm.wav",
	"./sfx/explode.wav",
	"./sfx/missile.wav"
};

void play_sound(SoundType t)
{
	int x;
	switch (t)
	{
	case SOUND_EXPLODE:
		x = PlaySound(TEXT("sfx/explode.wav"), NULL, SND_FILENAME | SND_ASYNC);
		printf("%d\n", x);
		break;
	}
}