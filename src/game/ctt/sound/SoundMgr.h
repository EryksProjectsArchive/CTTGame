//////////////////////////////////////////////
//
//         City Transport Tycoon
//     Copyright (C) Black Ice Mountains
//          All rights reserved
//
// File     : sound/SoundMgr.h
// Author   : Patryk Ławicki
//            
//
//////////////////////////////////////////////

#pragma once

enum SoundType
{
	SOUND_TYPE_MUSIC,
	SOUND_TYPE_EFFECT,
	SOUND_TYPEs_COUNT
};

#include "Sound.h"

enum SoundAPIs
{
	SOUND_API_NOAPI,
	SOUND_API_OPENAL,
	SOUND_APIs_COUNT
};

class ISoundMgr
{

public:
	ISoundMgr();
	virtual ~ISoundMgr();

	virtual bool setup();
	virtual ISound* createSound(SoundType type);

	static ISoundMgr* create(SoundAPIs api);
	static SoundAPIs getAPIIdFromString(const char *api);
};