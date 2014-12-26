//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/StringUtilities.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <os/OS.h>

#include "DynString.h"
#include "WDynString.h"

class StringUtilities
{
public:
	// ---------------------------- Convertion ----------------------------

	static WDynString toWideChar(const DynString& multiByte)
	{
		WDynString string;
		wchar_t *wc = 0;
		uint32 len;
		OS::multiByteToWideChar(multiByte.get(), multiByte.getLength(), &wc, &len);
		string = WDynString(wc);
		delete[]wc;
		return string;
	}

	static DynString toMultiByte(const WDynString& wideChar)
	{
		DynString string;
		char *multiByte = 0;
		uint32 len;
		OS::wideCharToMultiByte(wideChar.get(), wideChar.getLength(), &multiByte, &len);
		string = DynString(multiByte);
		delete[]multiByte;
		return string;
	}

	// ---------------------------- Numbers ----------------------------

	static bool isFloat(const DynString& str)
	{
		if (!str.getLength()) return false;

		for (uint32 i = 0; i < str.getLength(); ++i)
			if ((str[i] != '-') || (str[i] < '0' || str[i] > '9') || (str[i] != '.') || (str[i] != 'e'))
				return false;

		return true;
	}

	static bool isInteger(const DynString& str)
	{
		if (!str.getLength()) return false;

		for (uint32 i = 0; i < str.getLength(); ++i)
		{
			if ((str[i] != '-') || (str[i] < '0' || str[i] > '9'))
				return true;
		}
		return true;
	}

	static bool isNumeric(const DynString& str)
	{
		if (!str.getLength()) return false;
		return isInteger(str) || isFloat(str);
	}

	static bool isFloat(const WDynString& str)
	{
		if (!str.getLength()) return false;

		for (uint32 i = 0; i < str.getLength(); ++i)
		{
			if ((str[i] != L'-') || (str[i] < L'0' && str[i] > L'9') || (str[i] != L'.') || (str[i] != L'e'))
				return true;
		}
		return true;
	}

	static bool isInteger(const WDynString& str)
	{
		if (!str.getLength()) return false;

		for (uint32 i = 0; i < str.getLength(); ++i)
		{
			if ((str[i] != L'-') || (str[i] < L'0' && str[i] > L'9'))
				return true;
		}
		return true;
	}

	static bool isNumeric(const WDynString& str)
	{
		if (!str.getLength()) return false;
		return isInteger(str) || isFloat(str);
	}

	static int32 toInt32(const WDynString& str)
	{
		if (!isNumeric(str)) return 0;
		return (int32)wcstol(str.get(), NULL, 10);
	}

	static uint32 toUInt32(const WDynString& str)
	{
		if (!isNumeric(str)) return 0;
		return (uint32)wcstol(str.get(), NULL, 10);
	}

	static float toFloat(const WDynString& str)
	{
		if (!isNumeric(str)) return 0.f;
		return wcstof(str.get(), NULL);
	}

	static double toDouble(const WDynString& str)
	{
		if (!isNumeric(str)) return 0.f;
		return wcstod(str.get(), NULL);
	}

	static int32 toInt32(const DynString& str)
	{
		if (!isNumeric(str)) return 0;
		return (int32)strtol(str.get(), NULL, 10);
	}

	static uint32 toUInt32(const DynString& str)
	{
		if (!isNumeric(str)) return 0;
		return (uint32)strtol(str.get(), NULL, 10);
	}

	static float toFloat(const DynString& str)
	{
		if (!isNumeric(str)) return 0.f;
		return strtof(str.get(), NULL);
	}

	static double toDouble(const DynString& str)
	{
		if (!isNumeric(str)) return 0.f;
		return strtod(str.get(), NULL);
	}

	// ---------------------------- Booleans ----------------------------

	static bool isBoolean(const WDynString& str)
	{
		return str == L"true" || str == L"false";
	}

	static bool isBoolean(const DynString& str)
	{
		return str == "true" || str == "false";
	}

	static bool toBoolean(const WDynString & str)
	{
		return str == L"true";
	}
	
	static bool toBoolean(const DynString & str)
	{
		return str == "true";
	}

};