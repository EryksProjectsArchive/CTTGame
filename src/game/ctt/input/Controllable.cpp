//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: input/Controllable.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Controllable.h"

#include "Input.h"

Controllable::Controllable()
{
	registerInput();
}

Controllable::~Controllable()
{
	unregisterInput();
}

void Controllable::registerInput()
{
	Input::get()->addControllable(this);
}

void Controllable::unregisterInput()
{
	Input::get()->removeControllable(this);
}

Input * Controllable::input()
{
	return Input::get();
}