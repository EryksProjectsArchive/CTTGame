//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: input/Input.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include <core/Singleton.h>
#include <core/List.h>

#include "Controllable.h"

class Input : public Singleton<Input>
{
private:
	List<Controllable *> m_controllables;
public:
	Input();
	~Input();

private:
	void addControllable(Controllable *controllable);
	void removeControllable(Controllable *controllable);

	friend class Controllable;
};