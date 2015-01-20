//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/threading/Mutex.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <core/DynString.h>
#include <os/OS.h>

class Mutex
{
private:
	OS::MutexHandle m_mutexHandle;
	uint32 m_lockCount;
public:
	Mutex(const DynString& name = "");
	~Mutex();

	void lock(uint32 waitTime = MUTEX_WAIT_INFIITE);
	void unlock();
	bool tryLock(uint32 waitTime = 0);
};