//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: resources/sounds/wav/WAVsoundLoader.cpp
// Author	: Patryk £awicki
//
//////////////////////////////////////////////

#include "WAVsoundLoader.h"

#include <sound/SoundData.h>
#include <al.h>

#include <io/fs/FileSystem.h>


namespace WAV
{
	SoundLoader::SoundLoader()
	{

	}

	SoundLoader::~SoundLoader()
	{

	}


	bool SoundLoader::isFileValid(const FilePath& filePath)
	{
		bool isValid = false;
		if (filePath.find(".wav") != -1)
		{
			File *file = FileSystem::get()->open(filePath, FileOpenMode::Binary);
			if (file->isLoaded())
			{
				int8 id[5] = { 0 };
				file->read(id, 4, 1);
				isValid = (id[0] == 'R' && id[1] == 'I' && id[2] == 'F' && id[3] == 'F');
				file->seek(8, SeekOrigin::Type::Set);
				file->read(id, 4, 1);
				isValid = isValid &&(id[0] == 'W' && id[1] == 'A' && id[2] == 'V' && id[3] == 'E');
				file->seek(12, SeekOrigin::Type::Set);
				file->read(id, 4, 1);
				isValid = isValid&&(id[0] == 'f' && id[1] == 'm' && id[2] == 't' && id[3] == ' ');
				file->seek(36, SeekOrigin::Type::Set);
				file->read(id, 4, 1);
				isValid = isValid&&(id[0] == 'd' && id[1] == 'a' && id[2] == 't' && id[3] == 'a');

				FileSystem::get()->close(file);
			}
		}
		return isValid;
	}

	SoundData * SoundLoader::load(const FilePath& filePath)
	{
		// Recursive loading
		SoundData *data = 0;
		if (data = ::SoundLoader::load(filePath))
			return data;

		File *file = FileSystem::get()->open(filePath, FileOpenMode::Binary);
		if (file->isLoaded())
		{
			WaveFile waveFile = { 0 };
			file->read(&waveFile, sizeof(WaveFile) - sizeof(waveFile.data.Data), 1);
			if (waveFile.info.AudioFormat == 1)
			{
				data = new SoundData();
				if ((waveFile.info.NumChannels == 1 || waveFile.info.NumChannels == 2) && (waveFile.info.BitsPerSample == 8 || waveFile.info.BitsPerSample == 16))
				{
					if (waveFile.info.NumChannels == 1 && waveFile.info.BitsPerSample == 8)
					{
						data->format = AL_FORMAT_MONO8;
					}
					else if (waveFile.info.NumChannels == 1 && waveFile.info.BitsPerSample == 16)
					{
						data->format = AL_FORMAT_MONO16;
					}
					else if (waveFile.info.NumChannels == 2 && waveFile.info.BitsPerSample == 8)
					{
						data->format = AL_FORMAT_STEREO8;
					}
					else if (waveFile.info.NumChannels == 2 && waveFile.info.BitsPerSample == 16)
					{
						data->format = AL_FORMAT_STEREO16;
					}

					data->size = waveFile.data.ChunkSize;
					data->sampleRate = waveFile.info.SampleRate;
					data->data = new uint8[waveFile.data.ChunkSize];
					file->read(data->data, waveFile.data.ChunkSize, 1);
				}
				else {
					Error("WAVSoundLoader", "Sound is not correctly formatted");
				}
			}
			else {
				Error("WAVSoundLoader", "Sound is not PCM!");
			}

		FileSystem::get()->close(file);
		}
		return data;
	}
};