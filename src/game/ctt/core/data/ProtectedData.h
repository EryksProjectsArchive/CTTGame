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
	uint8 m_data[sizeof(T)];
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
		uint8 * _data = reinterpret_cast<uint8 *>(&data);
		for (uint32 i = 0; i < sizeof(T); ++i)
		{
			m_data[i] = ~(_data[i] ^ g_protectMagic);
		}		
	}

	T get()
	{
		uint8 outBuffer[sizeof(T)] = { 0 };
		for (uint32 i = 0; i < sizeof(T); ++i)
		{
			outBuffer[i] = ~(m_data[i] ^ g_protectMagic);
		}
		return *reinterpret_cast<T *>(outBuffer);
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