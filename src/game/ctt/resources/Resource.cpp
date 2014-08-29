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

Resource::Resource(FilePath filePath)
	: m_filePath(filePath), m_isLoaded(false)
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

bool Resource::load()
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