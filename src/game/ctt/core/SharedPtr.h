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

template <class Type>
class SharedPtr
{
private:
	Type * m_value;
	unsigned int * m_refCount;

public:
	SharedPtr()
		: m_refCount(new unsigned int), m_value(0)
	{
		*m_refCount = 1;
	}

	SharedPtr(Type * value)
		: m_refCount(new unsigned int), m_value(value)
	{
		*m_refCount = 1;
	}

	SharedPtr(const SharedPtr& sharedPtr)
		: m_refCount(sharedPtr.m_refCount), m_value(sharedPtr.m_value)
	{
		++ *m_refCount;
	}

	~SharedPtr()
	{
		if (--*m_refCount <= 0)
		{
			delete m_value;	
			delete m_refCount;
		}
	}

	operator Type& () { return m_value; }
	operator Type*() { return m_value; }
	Type * operator*() { return m_value; }
	Type * operator->() { return m_value; }
	Type& operator&() { return m_value; }

	SharedPtr<Type>& operator=(const SharedPtr& sharedPtr)
	{
		m_refCount = sharedPtr.m_refCount;
		m_value = sharedPtr.m_value;
		*m_refCount++;
		return *this;
	}
};