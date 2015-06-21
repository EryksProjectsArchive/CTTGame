//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/application/Application.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Application.h"

Application::Application() : m_isInitialized(false), m_isRunning(false)
{

}

Application::~Application()
{

}

bool Application::init()
{
	return false;
}

bool Application::pulse()
{
	return false;
}

void Application::shutdown()
{
	m_isRunning = false;
}