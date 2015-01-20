//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/threading/Mutex.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Mutex.h"

Mutex::Mutex(const DynString& name)
{
	OS::initializeMutex(&m_mutexHandle, name);
	m_lockCount = 0;
}

Mutex::~Mutex()
{
	while (m_lockCount > 0)
		unlock();

	OS::destroyMutex(&m_mutexHandle);
}

void Mutex::lock(uint32 waitTime)
{
	OS::lockMutex(&m_mutexHandle, waitTime);
	m_lockCount++;
}

void Mutex::unlock()
{
	OS::unlockMutex(&m_mutexHandle);
	m_lockCount--;
}

bool Mutex::tryLock(uint32 waitTime)
{
	if (waitTime == 0)
	{
		if (OS::tryLockMutex(&m_mutexHandle))
		{
			m_lockCount++;
			return true;
		}
	}
	else 
	{
		uint64 start = OS::getMicrosecondsCount();
		uint64 now = OS::getMicrosecondsCount();
		while (((now - start)/1000) <= waitTime)
		{
			if (OS::tryLockMutex(&m_mutexHandle))
			{
				m_lockCount++;
				return true;
			}

			now = OS::getMicrosecondsCount();
		}
	}
	return false;
}