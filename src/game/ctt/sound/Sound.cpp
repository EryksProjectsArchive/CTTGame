//////////////////////////////////////////////
//
//         City Transport Tycoon
//     Copyright (C) Black Ice Mountains
//          All rights reserved
//
// File     : sound/Sound.cpp
// Author   : Patryk Ławicki
//            
//
//////////////////////////////////////////////

#include <core/Logger.h>
#include <resources/SoundLoader.h>
#include <sound/SoundData.h>

#include "Sound.h"

Sound::Sound(OpenAL::Impl *al)
{
	m_al = al;
	m_sourceID = 0;
	m_bufferID = 0;
}

Sound::~Sound()
{
	if (m_sourceID)
	{
		m_al->alDeleteSources(1, &m_sourceID);
		m_sourceID = NULL;
	}
	if (m_bufferID)
	{
		m_al->alDeleteBuffers(1, &m_bufferID);
		m_bufferID = NULL;
	}
}

void Sound::play(bool loop)
{
	if (!isPlaying())
	{
		m_al->alSourcePlay(m_sourceID);
		m_al->alSourcei(m_sourceID, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
	}
}

void Sound::pause()
{
	m_al->alSourcePause(m_sourceID);
}

void Sound::stop()
{
	m_al->alSourceStop(m_sourceID);
}

void Sound::setVolume(float volume)
{
	m_al->alSourcef(m_sourceID, AL_GAIN, volume);
}

float Sound::getVolume()
{
	float volume = 0.0f;
	m_al->alGetSourcef(m_sourceID, AL_GAIN, &volume);
	return volume;
}

bool Sound::isPlaying()
{
	int State;
	m_al->alGetSourcei(m_sourceID, AL_SOURCE_STATE, &State);
	return State == AL_PLAYING;
}

bool Sound::load(const FilePath& filepath)
{
	SoundData * data = SoundLoader::get()->load(filepath);
	if (data)
	{
		m_al->alGenBuffers(1, &m_bufferID);
		m_al->alBufferData(m_bufferID, data->format, data->data, (ALsizei)data->size, data->sampleRate);
		m_al->alGenSources(1, &m_sourceID);
		m_al->alSourcei(m_sourceID, AL_BUFFER, m_bufferID);		
		m_al->alSourcef(m_sourceID, AL_MAX_DISTANCE, 10.0f);
		m_al->alSource3f(m_sourceID, AL_VELOCITY, 0.f, 0.f, 0.f);
		setPosition(Vector3(0.f, 0.f, 0.f));
		delete data;
		return true;
	}
	return false;
}

void Sound::setPosition(const Vector3& pos)
{
	m_al->alSourcei(m_sourceID, AL_SOURCE_RELATIVE, AL_FALSE);
	m_al->alSource3f(m_sourceID, AL_POSITION, pos.x, pos.y, pos.z);
}

void Sound::setListenerPosition(const Vector3& pos)
{
	m_al->alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
}

void Sound::setListenerOrientation(const Vector3& pos, const Vector3& up)
{
	float o[6] = { -pos.x, -pos.y, -pos.z, up.x, up.y, up.z };
	m_al->alListenerfv(AL_ORIENTATION, o);
}