//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: os/Linux/LinuxDynamicLibrary.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <os/DynamicLibrary.h>

namespace Linux
{
	class DynamicLibrary : public ::DynamicLibrary
	{
	private:
		void* m_module;
	public:
		DynamicLibrary(FilePath fileName);
		~DynamicLibrary() override;

		bool isValid() override;

		unsigned long getProcAddress(String<128> procName) override;
	};
};