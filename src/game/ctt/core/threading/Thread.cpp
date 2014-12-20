//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/threading/Thread.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Thread.h"

Thread::Thread(void(*callback)(void * data))
	: m_threadHandle(0)
{
	m_data.m_callback = callback;
	m_data.m_userData = 0;
}

Thread::~Thread()
{
	this->end(true);
}

void Thread::setUserData(void *userData)
{
	m_data.m_userData = userData;
}

void* Thread::getUserData()
{
	return m_data.m_userData;
}

bool Thread::start()
{
	if (isRunning())
		return false;

	m_threadHandle = OS::createThread(&m_data);
	if (!m_threadHandle)
		return false;

	return true;
}

bool Thread::end(bool force /*= false*/)
{
	// If our thread is not running just leave this call.
	if (!isRunning())
		return false;

	if (force)
	{
		OS::terminateThread(m_threadHandle, 0);
	}
	else 
	{
		OS::waitForThread(m_threadHandle, INFINITE);
	}	
	OS::closeThread(m_threadHandle);
	m_threadHandle = 0;
	return true;
}

bool Thread::isRunning()
{
	return m_threadHandle != 0;
}