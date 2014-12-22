//////////////////////////////////////////////
//
//         City Transport Tycoon
//     Copyright (C) Black Ice Mountains
//          All rights reserved
//
// File     : sound/openal/OpenALImpl.h
// Author   : Patryk Ławicki
//            
//
//////////////////////////////////////////////

#pragma once

#include <stdio.h>
#ifdef _WIN32
#	include <Windows.h>
#	include <al.h>
#	include <alc.h>
#elif __linux__
#	include <AL/al.h>
#	include <AL/alc.h>
#	include <dlfcn.h>
#define __cdecl __attribute__((__cdecl__))
#endif

#include <os/DynamicLibrary.h>

namespace OpenAL
{
	class Impl
	{
	private:
		DynamicLibrary * m_openALDynLib;
		bool m_isValid;
	public:
		Impl();
		~Impl();

		bool setup();
		bool isValid();

		ALCdevice	*(__cdecl *alcOpenDevice)(const ALCchar *devicename);
		ALCboolean	(__cdecl *alcCloseDevice)(ALCdevice *device);

		ALCcontext	*(__cdecl *alcCreateContext)(ALCdevice *device, const ALCint* attrlist);
		ALCboolean	(__cdecl *alcMakeContextCurrent)(ALCcontext *context);
		void		(__cdecl *alcProcessContext)(ALCcontext *context);
		void		(__cdecl *alcSuspendContext)(ALCcontext *context);
		void		(__cdecl *alcDestroyContext)(ALCcontext *context);
		ALCcontext	*(__cdecl *alcGetCurrentContext)(void);
		ALCdevice	*(__cdecl *alcGetContextsDevice)(ALCcontext *context);
		ALCenum		(__cdecl *alcGetError)(ALCdevice *device);
		ALCboolean	(__cdecl *alcIsExtensionPresent)(ALCdevice *device, const ALCchar *extname);
		void		*(__cdecl *alcGetProcAddress)(ALCdevice *device, const ALCchar *funcname);
		ALCenum		(__cdecl *alcGetEnumValue)(ALCdevice *device, const ALCchar *enumname);
		const		ALCchar	*(__cdecl *alcGetString)(ALCdevice *device, ALCenum param);
		void		(__cdecl *alcGetIntegerv)(ALCdevice *device, ALCenum param, ALCsizei size, ALCint *data);
		ALCdevice	*(__cdecl *alcCaptureOpenDevice)(const ALCchar *devicename, ALCuint frequency, ALCenum format, ALCsizei buffersize);
		ALCboolean	(__cdecl *alcCaptureCloseDevice)(ALCdevice *device);
		void		(__cdecl *alcCaptureStart)(ALCdevice *device);
		void		(__cdecl *alcCaptureStop)(ALCdevice *device);
		void		(__cdecl *alcCaptureSamples)(ALCdevice *device, ALCvoid *buffer, ALCsizei samples);
		
		void		(__cdecl *alEnable)(ALenum capability);
		void		(__cdecl *alDisable)(ALenum capability);
		ALboolean	(__cdecl *alIsEnabled)(ALenum capability);
		const		ALchar *(__cdecl *alGetString)(ALenum param);
		void		(__cdecl *alGetBooleanv)(ALenum param, ALboolean* data);
		void		(__cdecl *alGetIntegerv)(ALenum param, ALint* data);
		void		(__cdecl *alGetFloatv)(ALenum param, ALfloat* data);
		void		(__cdecl *alGetDoublev)(ALenum param, ALdouble* data);
		ALboolean	(__cdecl * alGetBoolean)(ALenum param);
		ALint		(__cdecl *alGetInteger)(ALenum param);
		ALfloat		(__cdecl *alGetFloat)(ALenum param);
		ALdouble	(__cdecl *alGetDouble)(ALenum param);
		ALenum		(__cdecl *alGetError)(void);
		ALboolean	(__cdecl *alIsExtensionPresent)(const ALchar* extname);
		void		*(__cdecl *alGetProcAddress)(const ALchar* fname);
		ALenum		(__cdecl *alGetEnumValue)(const ALchar* ename);
		void		(__cdecl *alListenerf)(ALenum param, ALfloat value);
		void		(__cdecl *alListener3f)(ALenum param, ALfloat value1, ALfloat value2, ALfloat value3);
		void		(__cdecl *alListenerfv)(ALenum param, const ALfloat* values);
		void		(__cdecl *alListeneri)(ALenum param, ALint value);
		void		(__cdecl *alListener3i)(ALenum param, ALint value1, ALint value2, ALint value3);
		void		(__cdecl *alListeneriv)(ALenum param, const ALint* values);
		void		(__cdecl *alGetListenerf)(ALenum param, ALfloat* value);
		void		(__cdecl *alGetListener3f)(ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3);
		void		(__cdecl *alGetListenerfv)(ALenum param, ALfloat* values);
		void		(__cdecl *alGetListeneri)(ALenum param, ALint* value);
		void		(__cdecl *alGetListener3i)(ALenum param, ALint *value1, ALint *value2, ALint *value3);
		void		(__cdecl *alGetListeneriv)(ALenum param, ALint* values);
		void		(__cdecl *alGenSources)(ALsizei n, ALuint* sources);
		void		(__cdecl *alDeleteSources)(ALsizei n, const ALuint* sources);
		ALboolean	(__cdecl *alIsSource)(ALuint sid);
		void		(__cdecl *alSourcef)(ALuint sid, ALenum param, ALfloat value);
		void		(__cdecl *alSource3f)(ALuint sid, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3);
		void		(__cdecl *alSourcefv)(ALuint sid, ALenum param, const ALfloat* values);
		void		(__cdecl *alSourcei)(ALuint sid, ALenum param, ALint value);
		void		(__cdecl *alSource3i)(ALuint sid, ALenum param, ALint value1, ALint value2, ALint value3);
		void		(__cdecl *alSourceiv)(ALuint sid, ALenum param, const ALint* values);
		void		(__cdecl *alGetSourcef)(ALuint sid, ALenum param, ALfloat* value);
		void		(__cdecl *alGetSource3f)(ALuint sid, ALenum param, ALfloat* value1, ALfloat* value2, ALfloat* value3);
		void		(__cdecl *alGetSourcefv)(ALuint sid, ALenum param, ALfloat* values);
		void		(__cdecl *alGetSourcei)(ALuint sid, ALenum param, ALint* value);
		void		(__cdecl *alGetSource3i)(ALuint sid, ALenum param, ALint* value1, ALint* value2, ALint* value3);
		void		(__cdecl *alGetSourceiv)(ALuint sid, ALenum param, ALint* values);
		void		(__cdecl *alSourcePlayv)(ALsizei ns, const ALuint *sids);
		void		(__cdecl *alSourceStopv)(ALsizei ns, const ALuint *sids);
		void		(__cdecl *alSourceRewindv)(ALsizei ns, const ALuint *sids);
		void		(__cdecl *alSourcePausev)(ALsizei ns, const ALuint *sids);
		void		(__cdecl *alSourcePlay)(ALuint sid);
		void		(__cdecl *alSourceStop)(ALuint sid);
		void		(__cdecl *alSourceRewind)(ALuint sid);
		void		(__cdecl *alSourcePause)(ALuint sid);
		void		(__cdecl *alSourceQueueBuffers)(ALuint sid, ALsizei numEntries, const ALuint *bids);
		void		(__cdecl *alSourceUnqueueBuffers)(ALuint sid, ALsizei numEntries, ALuint *bids);
		void		(__cdecl *alGenBuffers)(ALsizei n, ALuint* buffers);
		void		(__cdecl *alDeleteBuffers)(ALsizei n, const ALuint* buffers);
		ALboolean	(__cdecl *alIsBuffer)(ALuint bid);
		void		(__cdecl *alBufferData)(ALuint bid, ALenum format, const ALvoid* data, ALsizei size, ALsizei freq);
		void		(__cdecl *alBufferf)(ALuint bid, ALenum param, ALfloat value);
		void		(__cdecl *alBuffer3f)(ALuint bid, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3);
		void		(__cdecl *alBufferfv)(ALuint bid, ALenum param, const ALfloat* values);
		void		(__cdecl *alBufferi)(ALuint bid, ALenum param, ALint value);
		void		(__cdecl *alBuffer3i)(ALuint bid, ALenum param, ALint value1, ALint value2, ALint value3);
		void		(__cdecl *alBufferiv)(ALuint bid, ALenum param, const ALint* values);
		void		(__cdecl *alGetBufferf)(ALuint bid, ALenum param, ALfloat* value);
		void		(__cdecl *alGetBuffer3f)(ALuint bid, ALenum param, ALfloat* value1, ALfloat* value2, ALfloat* value3);
		void		(__cdecl *alGetBufferfv)(ALuint bid, ALenum param, ALfloat* values);
		void		(__cdecl *alGetBufferi)(ALuint bid, ALenum param, ALint* value);
		void		(__cdecl *alGetBuffer3i)(ALuint bid, ALenum param, ALint* value1, ALint* value2, ALint* value3);
		void		(__cdecl *alGetBufferiv)(ALuint bid, ALenum param, ALint* values);
		void		(__cdecl *alDopplerFactor)(ALfloat value);
		void		(__cdecl *alDopplerVelocity)(ALfloat value);
		void		(__cdecl *alSpeedOfSound)(ALfloat value);
		void		(__cdecl *alDistanceModel)(ALenum distanceModel);

	};
};
