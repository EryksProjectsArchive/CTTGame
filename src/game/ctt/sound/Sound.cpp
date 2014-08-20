//////////////////////////////////////////////
//
//         City Transport Tycoon
//     Copyright (C) Black Ice Mountains
//          All rights reserved
//
// File     : sound/Sound.cpp
// Author   : Patryk Ławicki
//            
//
//////////////////////////////////////////////

#include "Sound.h"

ISound::ISound()
{
}

ISound::~ISound()
{
}

bool ISound::load(const char* filename)
{
	return false;
}

void ISound::play(bool loop)
{
}

bool ISound::isPlaying()
{
	return false;
}