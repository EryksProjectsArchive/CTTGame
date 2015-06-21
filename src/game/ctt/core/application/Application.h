//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/application/Application.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

class Application
{
protected:
	bool m_isRunning;
	bool m_isInitialized;
public:
	Application();
	virtual ~Application();
	virtual bool init();

	virtual bool pulse();
	virtual void shutdown();
};