//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: os/win32/Win32DynamicLibrary.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Win32DynamicLibrary.h"

namespace Win32
{
	DynamicLibrary::DynamicLibrary(const FilePath& fileName) : ::DynamicLibrary(fileName)
	{
		m_hModule = LoadLibrary(fileName);
	}

	DynamicLibrary::~DynamicLibrary()
	{
		if (m_hModule)
		{
			FreeModule(m_hModule);
			m_hModule = 0;
		}
	}

	bool DynamicLibrary::isValid()
	{
		return m_hModule != 0;
	}

	unsigned long DynamicLibrary::getProcAddress(const String<128>& procName)
	{
		if (m_hModule)
		{
			return (unsigned long)GetProcAddress(m_hModule, procName);
		}
		return 0;
	}
};
	