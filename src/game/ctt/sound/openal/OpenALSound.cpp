//////////////////////////////////////////////
//
//         City Transport Tycoon
//     Copyright (C) Black Ice Mountains
//          All rights reserved
//
// File     : sound/openal/OpenALSound.cpp
// Author   : Patryk Ławicki
//            
//
//////////////////////////////////////////////

#include <cstring>
#include <core/Logger.h>
#include <sound/WaveFile.h>

#include "OpenALSound.h"

namespace OpenAL
{
	Sound::Sound(Impl *al)
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
			m_al->alSourcei(m_sourceID, AL_LOOPING, loop?AL_TRUE:AL_FALSE);
		}
	}

	bool Sound::isPlaying()
	{
		int State;
		m_al->alGetSourcei(m_sourceID, AL_SOURCE_STATE, &State);
		return State == AL_PLAYING;
	}

	bool Sound::load(const char* filename)
	{
		FILE *fp = NULL;
		fp = fopen(filename, "r+");
		if (!fp)
		{
			Error("Cloud not open : %s!", filename);
			fclose(fp);
			return false;
		}

		WaveFile file;
		fread(&file, sizeof(WaveFile)-sizeof(file.data.Data), 1, fp);

		if (strncmp(file.header.ChunkID, "RIFF", 4))
		{
			Error("sound_load", "Not RIFF!");
			fclose(fp);
			return false;
		}

		if (strncmp(file.header.Format, "WAVE", 4))
		{
			Error("sound_load", "Not WAVE!");
			fclose(fp);
			return false;
		}

		if (strncmp(file.info.ChunkID, "fmt ", 4))
		{
			Error("sound_load", "Corrupt!");
			fclose(fp);
			return false;
		}

		if (strncmp(file.data.ChunkID, "data", 4))
		{
			Error("sound_load", "Corrupt!");
			fclose(fp);
			return false;
		}

		if (file.info.AudioFormat != 1)
		{
			Error("sound_load", "Audio is not PCM!");
			fclose(fp);
			return false;
		}

		int format = NULL;
		if (file.info.NumChannels == 1 && file.info.BitsPerSample == 8)
		{
			format = AL_FORMAT_MONO8;
		}
		else if (file.info.NumChannels == 1 && file.info.BitsPerSample == 16)
		{
			format = AL_FORMAT_MONO16;
		}
		else if (file.info.NumChannels == 2 && file.info.BitsPerSample == 8)
		{
			format = AL_FORMAT_STEREO8;
		}
		else if (file.info.NumChannels == 2 && file.info.BitsPerSample == 16)
		{
			format = AL_FORMAT_STEREO16;
		}
		else
		{
			Error("sound_load", "Audio is not correctly formatted");
			fclose(fp);
			return false;
		}

		file.data.Data = new unsigned char[file.data.ChunkSize];
		fread(file.data.Data, sizeof(char), file.data.ChunkSize, fp);

		fclose(fp);

		m_al->alGenBuffers(1, &m_bufferID);
		m_al->alBufferData(m_bufferID, format, file.data.Data, file.data.ChunkSize, file.info.SampleRate);
		m_al->alGenSources(1, &m_sourceID);
		m_al->alSourcei(m_sourceID, AL_BUFFER, m_bufferID);
		delete[]file.data.Data;
		return true;
	}
};
