//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: input/Controllable.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

class Controllable
{
public:
	Controllable();
	virtual ~Controllable();

protected:
	virtual void registerBinds(Input *input) = 0;
	virtual void unregisterBinds(Input *input) = 0;

	void registerInput();
	void unregisterInput();

	friend class Input;
};