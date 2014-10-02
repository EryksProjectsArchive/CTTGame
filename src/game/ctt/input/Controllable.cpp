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
	Input::get()->addControllable(this);
}

Controllable::~Controllable()
{
	Input::get()->removeControllable(this);
}

void Controllable::registerBinds(Input *input)
{

}

void Controllable::unregisterBinds(Input *input)
{

}