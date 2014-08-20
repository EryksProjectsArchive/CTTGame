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

void ISound::pause()
{
}

void ISound::stop()
{
}

void ISound::setVolume(float volume)
{
}

float ISound::getVolume()
{
	return 0.0f;
}

bool ISound::isPlaying()
{
	return false;
}