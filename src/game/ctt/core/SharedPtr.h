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

template <class type>
class SharedPtr
{
private:
	type * m_value;
	uint32 * m_refCount;

public:
	SharedPtr() : m_refCount(0), m_value(0) {}

	explicit SharedPtr(type * value) 
		: m_refCount(value ? new uint32(1) : NULL), m_value(value) 
	{
	}

	SharedPtr(const SharedPtr& sharedPtr)
		: m_refCount(sharedPtr.m_refCount), m_value(sharedPtr.m_value)
	{
		if (m_value)
		{
			++(*m_refCount);
		}
	}

	~SharedPtr()
	{		
		if (isNull())
		{
			return;
		}

		if (--(*m_refCount) <= 0)
		{
			delete m_value;
			delete m_refCount;
		}

		m_value = 0;
		m_refCount = 0;
	}

	type * operator->() 
	{ 
		return m_value; 
	}

	type & operator*() 
	{ 
		return *m_value;  
	}

	operator type()
	{
		return m_value;
	}

	bool isNull() { return m_value == NULL; }

	operator bool()
	{
		return m_value != NULL;
	}

	SharedPtr& operator=(const SharedPtr& sharedPtr)
	{
		if (sharedPtr == *this)
		{
			return *this;
		}

		if (m_refCount)
		{
			delete m_refCount;
		}

		m_refCount = sharedPtr.m_refCount;
		m_value = sharedPtr.m_value;

		if (m_value)
		{
			(*m_refCount)++;
		}
		return *this;
	}
};

// Global operator overload
template <class A, class B> 
inline bool operator==(const SharedPtr<A> a, const SharedPtr<B> b)
{
	return &a == &b;
}