//////////////////////////////////////////////
//
//         City Transport Tycoon
//     Copyright (C) Black Ice Mountains
//          All rights reserved
//
// File     : sound/SoundManager.cpp
// Author   : Patryk Ławicki
//            
//
//////////////////////////////////////////////

#include <cstring>

#include "SoundManager.h"

SoundManager::SoundManager()
{
	m_context = 0;
	m_device = 0;
	m_al = new OpenAL::Impl();
}

SoundManager::~SoundManager()
{
	for (uint32 i = 0; i < SoundType::COUNT; ++i)
	{
		for (Sound * sound : m_sounds[i])
			delete sound;
	
		m_sounds[i].clear();
	}

	if (m_al && m_al->isValid())
	{
		m_al->alcMakeContextCurrent(0);
		if (m_context)
		{
			m_al->alcDestroyContext(m_context);
			m_context = 0;
		}
		if (m_device)
		{
			m_al->alcCloseDevice(m_device);
			m_device = 0;
		}

		delete m_al;
		m_al = 0;
	}
}

bool SoundManager::setup()
{
	if (m_al->setup())
	{
		const char * defaultDevice = m_al->alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);

		m_device = m_al->alcOpenDevice(defaultDevice);
		if (m_device == NULL)
		{
			return false;
		}

		//Create a context
		m_context = m_al->alcCreateContext(m_device, NULL);

		//Set active context
		m_al->alcMakeContextCurrent(m_context);

		// Print informations about OpenAL
		Info("SoundMgr", "OpenAL started version %s. [vendor: %s, renderer: %s]", m_al->alGetString(AL_VERSION), m_al->alGetString(AL_VENDOR), m_al->alGetString(AL_RENDERER));

		// Clear Error Code
		m_al->alGetError();
		return true;
	}
	return false;
}

Sound * SoundManager::createSound(SoundType::Type type)
{
	Sound *sound = new Sound(m_al);
	m_sounds[type].pushBack(sound);
	return sound;
}