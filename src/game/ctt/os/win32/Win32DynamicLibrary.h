//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: os/win32/Win32DynamicLibrary.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <os/DynamicLibrary.h>

#include <Windows.h>

namespace Win32
{
	class DynamicLibrary : public ::DynamicLibrary
	{
	private:
		HMODULE m_hModule;
	public:
		DynamicLibrary(FilePath fileName);
		~DynamicLibrary() override;

		bool isValid() override;

		unsigned long getProcAddress(String<128> procName) override;
	};
};