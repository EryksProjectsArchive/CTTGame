//////////////////////////////////////////////
//
//         City Transport Tycoon
//     Copyright (C) Black Ice Mountains
//          All rights reserved
//
// File     : sound/Sound.h
// Author   : Patryk Ławicki
//            
//
//////////////////////////////////////////////

#pragma once

#include <sound/openal/OpenALImpl.h>

class Sound
{
private:
	OpenAL::Impl* m_al;

	uint32 m_bufferID;
	uint32 m_sourceID;
public:
	Sound(OpenAL::Impl* al);
	~Sound();

	bool load(const FilePath& filepath);

	void play(bool loop = false);
	void pause();
	void stop();

	void setVolume(float volume);
	float getVolume();

	bool isPlaying();
};