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
	~Controllable();

protected:
	virtual void registerBinds(Input *input);
	virtual void unregisterBinds(Input *input);

	friend class Input;
};