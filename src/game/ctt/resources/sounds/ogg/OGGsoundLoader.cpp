//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: resources/sounds/ogg/OGGsoundLoader.cpp
// Author	: Patryk £awicki
//
//////////////////////////////////////////////

#include "OGGsoundLoader.h"

#include <sound/SoundData.h>
#include <al.h>

#include <vorbis/codec.h>
#include <vorbis/vorbisenc.h>
#include <vorbis/vorbisfile.h>

#include <io/fs/FileSystem.h>

#include <vector>


namespace OGG
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
		if (filePath.find(".ogg") != -1)
		{
			File *file = FileSystem::get()->open(filePath, FileOpenMode::Binary);
			if (file->isLoaded())
			{
				int8 id[5] = { 0 };
				file->read(id, 4, 1);
				isValid = isValid &&(id[0] == 'O' && id[1] == 'g' && id[2] == 'g' && id[3] == 'S');
				file->seek(29, SeekOrigin::Type::Set);
				int8 ids[7] = { 0 };
				file->read(ids, 6, 1);
				isValid = isValid &&(ids[0] == 'v' && ids[1] == 'o' && ids[2] == 'r' && ids[3] == 'b' && ids[4] == 'i' && ids[5] == 's');

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
			data = new SoundData();
			ov_callbacks callbacks = 
			{
				fileRead,
				fileSeek,
				fileClose,
				fileTell

			};
			OggVorbis_File vorbis_file;
			vorbis_info* vi;
			uint32 data_size;
			uint32 size = 0;
			int32 bitstream;
			
			if (ov_open_callbacks(file, &vorbis_file, NULL, 0, callbacks) == 0)
			{
				vi = ov_info(&vorbis_file, -1);
				if (vi)
				{
					if (vi->channels == 1)
					{
						data->format = AL_FORMAT_MONO16;
					}
					else if (vi->channels == 2)
					{
						data->format = AL_FORMAT_STEREO16;
					}

					data->sampleRate = vi->rate;

					data_size = ov_pcm_total(&vorbis_file, -1) * vi->channels * 2;

					ov_pcm_seek(&vorbis_file, 0);

					data->data = new uint8[data_size];
					data->size = data_size;

					while (size < data_size)
					{
						int32 result = ov_read(&vorbis_file, (int8*)data->data + size, data_size - size, 0, 2, 1, &bitstream);

						if (result > 0)
						{
							size += result;
						}
					}
				}
				else
				{
					Error("OGGSoundLoader", "Cannot get informations about audio from ogg file '%s'.", filePath.get());
				}
			}
			else
			{
				Error("OGGSoundLoader", "Cannot setup ogg callbacks.");
			}

			ov_clear(&vorbis_file);

			FileSystem::get()->close(file);
		}
		return data;
	}

	size_t SoundLoader::fileRead(void* buffer, size_t size, size_t n, void* datasource)
	{
		File* file = (File *)datasource;

		size_t bytes = size * n;
		file->read(buffer, 1, bytes);

		return n;
	}

	int SoundLoader::fileSeek(void* datasource, ogg_int64_t offset, int whence)
	{
		switch (whence)
		{
		case SEEK_SET: 
			(static_cast<File*> (datasource)->seek((int)offset, SeekOrigin::Set));   
			break;
		case SEEK_CUR: 
			(static_cast<File*> (datasource)->seek((int)offset, SeekOrigin::Current)); 
			break;
		case SEEK_END: 
			(static_cast<File*> (datasource)->seek((int)offset, SeekOrigin::End));    
			break;
		default: 
			return -1;
		}
		return 0;
	}


	int SoundLoader::fileClose(void* )
	{
		return 0;
	}

	long SoundLoader::fileTell(void* datasource) 
	{
		return (static_cast<File*> (datasource)->tell());
	}
};