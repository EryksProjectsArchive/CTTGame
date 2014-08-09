//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: os/Linux/LinuxDynamicLibrary.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "LinuxDynamicLibrary.h"

#include <dlfcn.h>

namespace Linux
{
	DynamicLibrary::DynamicLibrary(FilePath fileName) : ::DynamicLibrary(fileName)
	{
		m_module = dlopen(fileName,RTLD_NOW);
	}

	DynamicLibrary::~DynamicLibrary()
	{
		if (m_module)
		{
			dlclose(m_module);
			m_module = 0;
		}
	}

	bool DynamicLibrary::isValid()
	{
		return m_module != 0;
	}

	unsigned long DynamicLibrary::getProcAddress(String<128> procName)
	{
		if (m_module)
		{
			return (unsigned long)dlsym(m_module, procName);
		}
		return 0;
	}
};
	