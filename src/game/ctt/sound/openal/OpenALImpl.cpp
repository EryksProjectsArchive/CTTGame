//////////////////////////////////////////////
//
//         City Transport Tycoon
//     Copyright (C) Black Ice Mountains
//          All rights reserved
//
// File     : sound/openal/OpenALImpl.cpp
// Author   : Patryk Ławicki
//            
//
//////////////////////////////////////////////

#include <core/Logger.h>

#include "OpenALImpl.h"

namespace OpenAL
{
	Impl::Impl()
	{
        mModule = 0;
	}

	Impl::~Impl()
	{
        if(mModule)
        {
#ifdef _WIN32
            FreeLibrary(mModule);
#elif __linux__ 
            dlclose(mModule);
#endif
            mModule = 0;
		}
	}

	bool Impl::setup()
	{
#ifdef _WIN32
        mModule = LoadLibrary("OpenAL32.dll");
        if (mModule)
		{
			// Macro to make code looking slightly better.
#define METHOD(name)\
    *(unsigned int *)&name = (unsigned int)GetProcAddress(mModule, #name);\
    if(!name) { \
		Error("openAL", "Cannot find OpenAL Method - '%s'.",#name);\
		return false;\
	}
#elif __linux__
        mModule = dlopen("libopenal.so", RTLD_NOW);
        if (mModule)
        {
            // Macro to make code looking slightly better.
#define METHOD(name)\
    *(unsigned int *)&name = (unsigned int)dlsym(mModule, #name);\
    if(!name) { \
        Error("openAL", "Cannot find OpenAL Method - '%s'.",#name);\
        return false;\
    }

#endif
            METHOD(alGetProcAddress);

#define EXT_METHOD(name)\
    *(unsigned int *)&name = (unsigned int)alGetProcAddress(#name);\
    if(!name) { \
        Error("openAL", "Cannot find OpenAL Method - '%s'.",#name);\
        return false;\
    }

			METHOD(alcOpenDevice);
			METHOD(alcCloseDevice);
			METHOD(alcCreateContext);
			METHOD(alcMakeContextCurrent);
			METHOD(alcProcessContext);
			METHOD(alcSuspendContext);
			METHOD(alcDestroyContext);
			METHOD(alcGetCurrentContext);
			METHOD(alcGetContextsDevice);
			METHOD(alcGetError);
			METHOD(alcIsExtensionPresent);
			METHOD(alcGetProcAddress);
			METHOD(alcGetEnumValue);
			METHOD(alcGetString);
			METHOD(alcGetIntegerv);
			METHOD(alcCaptureOpenDevice);
			METHOD(alcCaptureCloseDevice);
			METHOD(alcCaptureStart);
			METHOD(alcCaptureStop);
			METHOD(alcCaptureSamples);

			METHOD(alEnable);
			METHOD(alDisable);
			METHOD(alIsEnabled);
			METHOD(alGetString);
			METHOD(alGetBooleanv);
			METHOD(alGetIntegerv);
			METHOD(alGetFloatv);
			METHOD(alGetDoublev);
			METHOD(alGetBoolean);
			METHOD(alGetInteger);
			METHOD(alGetFloat);
			METHOD(alGetDouble);
			METHOD(alGetError);
			METHOD(alIsExtensionPresent);
			METHOD(alGetEnumValue);
			METHOD(alListenerf);
			METHOD(alListener3f);
			METHOD(alListenerfv);
			METHOD(alListeneri);
			METHOD(alListener3i);
			METHOD(alListeneriv);
			METHOD(alGetListenerf);
			METHOD(alGetListener3f);
			METHOD(alGetListenerfv);
			METHOD(alGetListeneri);
			METHOD(alGetListener3i);
			METHOD(alGetListeneriv);
			METHOD(alGenSources);
			METHOD(alDeleteSources);
			METHOD(alIsSource);
			METHOD(alSourcef);
			METHOD(alSource3f);
			METHOD(alSourcefv);
			METHOD(alSourcei);
			METHOD(alSource3i);
			METHOD(alSourceiv);
			METHOD(alGetSourcef);
			METHOD(alGetSource3f);
			METHOD(alGetSourcefv);
			METHOD(alGetSourcei);
			METHOD(alGetSource3i);
			METHOD(alGetSourceiv);
			METHOD(alSourcePlayv);
			METHOD(alSourceStopv);
			METHOD(alSourceRewindv);
			METHOD(alSourcePausev);
			METHOD(alSourcePlay);
			METHOD(alSourceStop);
			METHOD(alSourceRewind);
			METHOD(alSourcePause);
			METHOD(alSourceQueueBuffers);
			METHOD(alSourceUnqueueBuffers);
			METHOD(alGenBuffers);
			METHOD(alDeleteBuffers);
			METHOD(alIsBuffer);
			METHOD(alBufferData);
			METHOD(alBufferf);
			METHOD(alBuffer3f);
			METHOD(alBufferfv);
			METHOD(alBufferi);
			METHOD(alBuffer3i);
			METHOD(alBufferiv);
			METHOD(alGetBufferf);
			METHOD(alGetBuffer3f);
			METHOD(alGetBufferfv);
			METHOD(alGetBufferi);
			METHOD(alGetBuffer3i);
			METHOD(alGetBufferiv);
			METHOD(alDopplerFactor);
			METHOD(alDopplerVelocity);
			METHOD(alSpeedOfSound);
			METHOD(alDistanceModel);

			return true;
		}
		else
        {
#ifdef _WIN32
            Error("openAL", "Cannot find OpenAL32.dll file.");
#elif __linux__ 
            Error("openAL", "Cannot find libopenal.so file.");
#endif
        }

		return false;
    }
};
