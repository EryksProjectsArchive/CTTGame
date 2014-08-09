//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/ProtectedPtr.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

template <class Type>
class ProtectedPtr
{
private:
	Type * m_value;

public:
	ProtectedPtr()
		: m_value(0)
	{		
	}

	ProtectedPtr(Type * value)
		: m_value(value)
	{
	}

	~ProtectedPtr()
	{
		if (m_value)
		{
			delete m_value;
			m_value = 0;
		}
	}

	operator Type*() { return m_value; }
	operator Type&() { return *m_value; }
	Type *operator *() { return m_value; }
	Type *operator->() { return m_value; }
	Type &operator&() { return *m_value; }

	ProtectedPtr& operator=(const ProtectedPtr& protectedPtr)
	{
		if (!m_value)
		{
			m_value = protectedPtr.m_value;
		}
	}

	ProtectedPtr& operator=(Type *value)
	{
		return *this;
	}
};