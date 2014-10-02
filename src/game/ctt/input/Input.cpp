//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: input/Input.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Input.h"
#include "Controllable.h"

Input::Input()
{

}

Input::~Input()
{

}

void Input::addControllable(Controllable *controllable)
{
	m_controllables.pushBack(controllable);

	controllable->registerBinds(this);
}

void Input::removeControllable(Controllable *controllable)
{
	controllable->unregisterBinds(this);

	m_controllables.remove(controllable);
}