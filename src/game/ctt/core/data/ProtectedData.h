//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/data/ProtectedData.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

static uint8 g_protectMagic = (uint8)'G';

template <typename T>
class ProtectedData
{
private:
	T m_data;
public:
	ProtectedData()
	{
	}

	ProtectedData(const ProtectedData& data)
	{
		m_data = data.m_data;
	}

	~ProtectedData()
	{
	}

	ProtectedData& operator=(ProtectedData& data)
	{
		m_data = data.m_data;
	}

	void set(T data)
	{
		for (uint32 i = 0; i < sizeof(T); ++i)
			*((uint8 *)&m_data + i) = ~(*((uint8 *)&data + i) ^ g_protectMagic);
	}

	T get()
	{
		uint8 outBuffer[sizeof(T)] = { 0 };
		for (uint32 i = 0; i < sizeof(T); ++i)
			*((uint8 *)&outBuffer + i) = ~(*((uint8 *)&m_data + i) ^ g_protectMagic);
		return *(T *)outBuffer;
	}

	inline T val() 
	{
		return get();
	}

	inline T value() 
	{
		return get();
	}

	ProtectedData& operator=(T value)
	{
		set(value);
		return *this;
	}

	operator T()
	{
		return get();
	}
};