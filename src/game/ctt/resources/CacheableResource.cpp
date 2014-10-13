//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: resources/CacheableResource.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "CacheableResource.h"

#include <core/Logger.h>

CacheableResource::CacheableResource(FilePath filePath) : Resource(filePath), m_refCount(0)
{
}

CacheableResource::~CacheableResource()
{
	if (m_refCount >= 1)
		Warning("cacheable resource", "There is still one or more references left in cachable resource '%s'. (%d)", m_filePath.get(), m_refCount);	

	destroy();
}

void CacheableResource::acquire()
{
	if (++m_refCount == 1)
	{
		if (!load())
		{
			Error("cacheable resource", "Cannot load cacheable resource! '%s'", m_filePath.get());
		}
		else 
		{
			Debug("cacheable resource", "Loaded cacheable resource. '%s'", m_filePath.get());
		}
	}
}

void CacheableResource::release()
{
	if (--m_refCount < 1)
	{
		destroy();
		Debug("cacheable resource", "Destroyed cacheable resource memory because ref count amount reached bellow 1. '%s'", m_filePath.get());
	}
}
