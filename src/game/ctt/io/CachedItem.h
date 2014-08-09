//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: io/CachedItem.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <core/String.h>

template <typename Type>
class CachedItem
{
private:
	FilePath m_path;
	unsigned char * m_refCount;
	Type *m_object;
public:
	CachedItem(FilePath path)
		: m_path(path), m_object(0), m_refCount(new unsigned char)
	{
		*m_refCount = 1;
	}

	CachedItem(const CachedItem& item)
		: m_path(item.m_path), m_object(item.m_object), m_refCount(item.m_refCount)
	{
		*m_refCount = 1;
	}

	~CachedItem()
	{
		if (*m_refCount <= 0)
		{
			m_object->destroy();
			delete m_object;
			m_object = 0;
		}
	}

	Type * operator->()
	{
		if (!m_object)
		{
			m_object = new Type();
			m_object->load(m_path);
			*m_refCount = 1;
		}
		return m_object;
	}

	Type * operator*()
	{
		if (!m_object)
		{
			m_object = new Type();
			m_object->load(m_path);
			*m_refCount = 1;
		}
		return m_object;
	}

	CachedItem& operator=(const CachedItem& item)
	{
		m_object = item.m_object;
		m_refCount = item.m_refCount;
		m_path = item.m_path;
		*m_refCount++;
		return *this;
	}
};