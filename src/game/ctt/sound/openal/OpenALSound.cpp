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
		mAL = al;
		mSourceID = 0;
		mBufferID = 0;
	}

	Sound::~Sound()
	{
		if (mSourceID)
		{
			mAL->alDeleteSources(1, &mSourceID);
			mSourceID = NULL;
		}
		if (mBufferID)
		{
			mAL->alDeleteBuffers(1, &mBufferID);
			mBufferID = NULL;
		}
	}

	void Sound::play()
	{
		if (!this->isPlaying())
		{
            //mAL->alSourcef(mSourceID, AL_GAIN, 1.01f);
			mAL->alSourcePlay(mSourceID);
		}
	}

	bool Sound::isPlaying()
	{
		int State;
		mAL->alGetSourcei(mSourceID, AL_SOURCE_STATE, &State);
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

		mAL->alGenBuffers(1, &mBufferID);
		mAL->alBufferData(mBufferID, format, file.data.Data, file.data.ChunkSize, file.info.SampleRate);
		mAL->alGenSources(1, &mSourceID);
		mAL->alSourcei(mSourceID, AL_BUFFER, mBufferID);
		delete[]file.data.Data;
		return true;
	}
};
