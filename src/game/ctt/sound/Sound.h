//////////////////////////////////////////////
//
//         City Transport Tycoon
//     Copyright (C) Black Ice Mountains
//          All rights reserved
//
// File     : sound/Sound.h
// Author   : Patryk Ławicki
//            
//
//////////////////////////////////////////////

#pragma once

class ISound
{
public:
	ISound();
	virtual ~ISound();

	virtual bool load(const char* filename);

	virtual void play();
	virtual bool isPlaying();
};