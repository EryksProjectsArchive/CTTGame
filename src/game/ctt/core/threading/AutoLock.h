//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/threading/AutoLock.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include "Mutex.h"

class AutoLock
{
private:
	Mutex& m_mutex;
public:
	AutoLock(Mutex& mutex) : m_mutex(mutex) 
	{
		m_mutex.lock();
	}

	AutoLock(Mutex* mutex) : m_mutex(*mutex)
	{
		m_mutex.lock();
	}

	~AutoLock()
	{
		m_mutex.unlock();
	}
};