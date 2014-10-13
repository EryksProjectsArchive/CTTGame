//////////////////////////////////////////////
//
//         City Transport Tycoon
//     Copyright (C) Black Ice Mountains
//          All rights reserved
//
// File     : sound/SoundManager.h
// Author   : Patryk Ławicki
//            
//
//////////////////////////////////////////////

#pragma once

#include <core/Singleton.h>
#include <core/List.h>

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

class SoundManager : public Singleton<SoundManager>
{
private:
	OpenAL::Impl* m_al;

	ALCcontext* m_context;
	ALCdevice* m_device;

	List<Sound *> m_sounds[SoundType::COUNT];

public:
	SoundManager();
	~SoundManager();

	bool setup();

	Sound* createSound(SoundType::Type type);
};