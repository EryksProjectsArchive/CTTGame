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

ISound * ISoundMgr::createSound(SoundType::Type type)
{
	return new ISound();
}

ISoundMgr * ISoundMgr::create(SoundAPI::Type api)
{
	if (api == SoundAPI::OpenAL)
		return new OpenAL::SoundMgr();

	return new ISoundMgr();
}

SoundAPI::Type ISoundMgr::getAPIIdFromString(const char *api)
{
	if (!strcmp(api, "al") || !strcmp(api, "oal") || !strcmp(api, "openal"))
		return SoundAPI::OpenAL;

	return SoundAPI::NoAPI;
}
