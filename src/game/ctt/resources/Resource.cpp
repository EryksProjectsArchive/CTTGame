//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: resources/Resource.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Resource.h"

Resource::Resource()
	: m_isLoaded(false)
{
}

Resource::~Resource()
{
	if (m_isLoaded)
	{
		destroy();
	}
}

void Resource::destroy()
{
	if (m_isLoaded)
	{

	}
}

bool Resource::load(FilePath path)
{
	if (!m_isLoaded)
	{
		m_isLoaded = true;
		return true;
	}
	return false;
}

bool Resource::isLoaded()
{
	return m_isLoaded;
}