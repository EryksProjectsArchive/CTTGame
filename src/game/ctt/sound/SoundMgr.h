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

struct SoundType
{
	enum Type
	{
		Music,
		Effect,
		COUNT
	};
};

#include "Sound.h"

struct SoundAPI
{
	enum Type
	{
		NoAPI,
		OpenAL,
		COUNT
	};
};

class ISoundMgr
{

public:
	ISoundMgr();
	virtual ~ISoundMgr();

	virtual bool setup();
	virtual ISound* createSound(SoundType::Type type);

	static ISoundMgr* create(SoundAPI::Type api);
	static SoundAPI::Type getAPIIdFromString(const char *api);
};