//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/SharedPtr.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>
#include <stdio.h>

template <class Type>
class SharedPtr
{
private:
	Type * m_value;
	unsigned int * m_refCount;

public:
	SharedPtr() : m_refCount(0), m_value(0) {}

	explicit SharedPtr(Type * value) : m_refCount(value?new unsigned int(1):NULL), m_value(value) {}

	SharedPtr(const SharedPtr& sharedPtr)
		: m_refCount(sharedPtr.m_refCount), m_value(sharedPtr.m_value)
	{
		if (m_value)
			++refCount();
	}

	unsigned int & refCount() { return *m_refCount;  }

	~SharedPtr()
	{		
		if (isNull())return;
		if (--refCount() <= 0)
		{
			delete m_value;
			delete m_refCount;
		}
		m_value = 0;
		m_refCount = 0;
	}

	Type * operator->() { return m_value; }
	Type & operator*() { return *m_value;  }

	bool isNull() { return m_value == NULL; }

	operator bool()
	{
		return m_value != NULL;
	}

	SharedPtr& operator=(const SharedPtr& sharedPtr)
	{
		if (sharedPtr == *this) return *this;
		m_refCount = sharedPtr.m_refCount;
		m_value = sharedPtr.m_value;
		if (m_value) refCount()++;
		return *this;
	}
};

template <class A, class B> 
inline bool operator==(const SharedPtr<A> a, const SharedPtr<B> b)
{
	return &a == &b;
}