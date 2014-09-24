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
	if (m_al)
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

		//Info("[OpenAL]", "OpenAL started version %s. (vendor: %s, renderer: %s)", mAL->alcGetString(NULL, AL_VERSION), mAL->alcGetString(NULL, AL_VENDOR), mAL->alcGetString(NULL, AL_RENDERER));

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

		// Clear Error Code
		m_al->alGetError();
		return true;
	}
	return false;
}

Sound * SoundManager::createSound(SoundType::Type type)
{
	return new Sound(m_al);
}