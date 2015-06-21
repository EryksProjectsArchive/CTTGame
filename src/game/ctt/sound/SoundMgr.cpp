//////////////////////////////////////////////
//
//         City Transport Tycoon
//     Copyright (C) Black Ice Mountains
//          All rights reserved
//
// File     : sound/SoundMgr.cpp
// Author   : Patryk Ławicki
//            
//
//////////////////////////////////////////////

#include <cstring>

#include "openal/OpenALSoundMgr.h"
#include "SoundMgr.h"

ISoundMgr::ISoundMgr()
{
}

ISoundMgr::~ISoundMgr()
{
}

bool ISoundMgr::setup()
{
	return false;
}

ISound * ISoundMgr::createSound(SoundType type)
{
	return new ISound();
}

ISoundMgr * ISoundMgr::create(SoundAPIs api)
{
	if (api == SOUND_API_OPENAL)
		return new OpenAL::SoundMgr();

	return new ISoundMgr();
}

SoundAPIs ISoundMgr::getAPIIdFromString(const char *api)
{
	if (!strcmp(api, "al") || !strcmp(api, "oal") || !strcmp(api, "openal"))
		return SOUND_API_OPENAL;

	return SOUND_API_NOAPI;
}
