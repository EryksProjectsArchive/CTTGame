//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/Singleton.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

template <class T>
class Singleton
{
public:
	static T * get()
	{
		static T ptr;
		return &ptr;
	}
};