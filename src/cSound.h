#pragma once
#include "stdafx.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

//Sound array size
#define NUM_SOUNDS 8

//Sound identifiers
enum {
	SOUND_AMBIENT,
	SOUND_SWISH,
	SOUND_WARP,
	SOUND_UNLOCK,
	SOUND_ENERGYFLOW,
	SOUND_BOUNCE,
	SOUND_PICKUP,
	SOUND_SCREWGRAVITY
};

class cSound
{
public:
	cSound(void);
	virtual ~cSound(void);

	bool Load();
	void Play(int sound_id);
	void PlayBounce(float vol);
	void Stop(int sound_id);
	void SmoothStop(int sound_id);
	void StopAll();
	void Update();

	char type[4];
	DWORD size, chunkSize;
	short formatType, channels;
	DWORD sampleRate, avgBytesPerSec;
	short bytesPerSample, bitsPerSample;
	DWORD dataSize;
};