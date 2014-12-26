//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/Instance.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

template <class T>
class Instance
{
private:
	static T * s_instance;
public:
	Instance()
	{
		s_instance = (T*)this;
	}

	static T * get()
	{
		return s_instance;
	}
};

#define SETUP_INSTANCE(T) T * Instance<T>::s_instance = 0