//////////////////////////////////////////////
//
//         City Transport Tycoon
//     Copyright (C) Black Ice Mountains
//          All rights reserved
//
// File     : sound/openal/OpenALSoundMgr.h
// Author   : Patryk Ławicki
//            
//
//////////////////////////////////////////////

#pragma once

#include <sound/SoundMgr.h>
#include "OpenALImpl.h"

namespace OpenAL
{
	class SoundMgr : public ISoundMgr
	{
	private:
		Impl * mAL;

		ALCcontext *mContext;
		ALCdevice *mDevice;
	public:
		SoundMgr();
		~SoundMgr();

		bool setup();

		ISound * createSound(SoundType type);
	};
}
