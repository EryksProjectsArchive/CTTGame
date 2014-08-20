//////////////////////////////////////////////
//
//         City Transport Tycoon
//     Copyright (C) Black Ice Mountains
//          All rights reserved
//
// File     : sound/openal/OpenALSound.h
// Author   : Patryk Ławicki
//            
//
//////////////////////////////////////////////
#pragma once

#include "OpenALImpl.h"
#include "OpenALSoundMgr.h"

namespace OpenAL
{
	class Sound : public ISound
	{
	private:
		Impl* m_al;

		unsigned int m_bufferID;
		unsigned int m_sourceID;

	public:
		Sound(Impl* al);
		~Sound() override;

		bool load(const char* filename) override;

		void play(bool loop = false) override;
		bool isPlaying() override;
	};
};