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
		Impl* m_al;

		ALCcontext* m_context;
		ALCdevice* m_device;
	public:
		SoundMgr();
		~SoundMgr() override;

		bool setup() override;

		ISound* createSound(SoundType::Type type) override;
	};
}
