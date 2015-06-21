//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/performance/Profiler.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>
#include <os/OS.h>

class Profiler
{
private:
	uint64 m_start;
	uint64 m_time;
public:
	Profiler()
	{
		m_start = m_time = 0ull;
	}
	virtual ~Profiler() {}

	virtual void start()
	{
		m_start = OS::getMicrosecondsCount();
	}

	virtual void end()
	{
		m_time = OS::getMicrosecondsCount() - m_start;
		m_start = 0ull;
	}

	virtual uint64 getTime()
	{
		return m_time;
	}
};

class ProfilerScope
{
private:
	Profiler *m_profiler;

public:
	ProfilerScope(Profiler *profiler)
		: m_profiler(profiler)
	{
		m_profiler->start();
	}

	~ProfilerScope()
	{
		m_profiler->end();
	}
};

#define _CONCAT(a,b) a ## b
#define CONCAT(a,b) _CONCAT(a,b)
#define PROFILER(profilerObject) ProfilerScope CONCAT(profiler, __LINE__)(&profilerObject)

/* EOF */
