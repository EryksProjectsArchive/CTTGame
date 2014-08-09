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
#include <os/OS.h>

#include "OpenALImpl.h"

namespace OpenAL
{
	Impl::Impl()
		: m_openALDynLib(0)
	{
	}

	Impl::~Impl()
	{
		if (m_openALDynLib)
        {
			delete m_openALDynLib;
			m_openALDynLib = 0;
		}
	}

	bool Impl::setup()
	{
#ifdef _WIN32
#define DYN_LIB_NAME "OpenAL32"
#elif __linux__
#define DYN_LIB_NAME "libopenal"
#endif
		m_openALDynLib = OS::openDynamicLibrary(DYN_LIB_NAME);
		if (m_openALDynLib)
		{
            // Macro to make code looking slightly better.
#define METHOD(name)\
    *(unsigned int *)&name = (unsigned int)m_openALDynLib->getProcAddress(#name);\
    if(!name) { \
        Error("openAL", "Cannot find OpenAL Method - '%s'.",#name);\
        return false;\
    }

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
            Error("openAL", "Cannot find %s dynamic library.", DYN_LIB_NAME);
        }
		return false;
    }
};
