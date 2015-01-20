//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/threading/Thread.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

class Thread;
#include <os/OS.h>

class Thread
{
private:
	OS::ThreadHandle m_threadHandle;
	OS::ThreadRunData m_data;
public:
	Thread(void(*callback)(void * data));
	~Thread();

	template <typename T>
	void setUserData(T* userData);

	template <typename T>
	T* getUserData();

	bool start();
	bool end(bool force = false);

	bool isRunning();
};