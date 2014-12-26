//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: Debugging.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <core/Logger.h>
#include <Windows.h>
#define BIM_ASSERT(expr, msg) \
	if(!(expr)) { \
		char message[512];\
		sprintf(message, "%s\n\nFile: %s\nLine:%d\n\n%s", #expr, __FILE__, __LINE__, msg);\
		MessageBox(NULL, message, "Error", MB_ICONERROR); \
		Error("assert", "%s", #expr); Error("assert", "File: %s, Line: %d", __FILE__, __LINE__); Error("assert", "%s", msg);\
		RaiseException(0xDEADBEEF, NULL, NULL, NULL);\
		}