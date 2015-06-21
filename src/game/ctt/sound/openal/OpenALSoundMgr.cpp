//////////////////////////////////////////////
//
//         City Transport Tycoon
//     Copyright (C) Black Ice Mountains
//          All rights reserved
//
// File     : sound/openal/OpenALSoundMgr.cpp
// Author   : Patryk Ławicki
//            
//
//////////////////////////////////////////////

#include <core/Logger.h>

#include "OpenALSoundMgr.h"
#include "OpenALSound.h"

namespace OpenAL
{
	SoundMgr::SoundMgr()
	{
		mContext = 0;
		mDevice = 0;
		mAL = new Impl();
	}

	SoundMgr::~SoundMgr()
	{
		if (mAL)
		{
			mAL->alcMakeContextCurrent(NULL);
			if (mContext)
			{
				mAL->alcDestroyContext(mContext);
				mContext = 0;
			}
			if (mDevice)
			{
				mAL->alcCloseDevice(mDevice);
				mDevice = 0;
			}

			delete mAL;
			mAL = NULL;
		}
	}

	bool SoundMgr::setup()
	{
		if (mAL->setup())
		{

			//Info("[OpenAL]", "OpenAL started version %s. (vendor: %s, renderer: %s)", this->mAL->alcGetString(NULL, AL_VERSION), this->mAL->alcGetString(NULL, AL_VENDOR), this->mAL->alcGetString(NULL, AL_RENDERER));

			const char * defaultDevice = mAL->alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);

			mDevice = mAL->alcOpenDevice(defaultDevice);
			if (mDevice == NULL)
			{
				return false;
			}

			//Create a context
			mContext = mAL->alcCreateContext(mDevice, NULL);

			//Set active context
			mAL->alcMakeContextCurrent(mContext);

			// Clear Error Code
			mAL->alGetError();
			return true;
		}
		else
		{

		}
		return false;
	}

	ISound * SoundMgr::createSound(SoundType type)
	{
		return new Sound(mAL);
	}
};