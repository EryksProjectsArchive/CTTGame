//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/environment/Environment.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Environment.h"

Environment::Environment()
{

}

Environment::~Environment()
{

}

void Environment::setSunPosition(glm::vec3 position)
{
	m_sunPosition = position;
}

glm::vec3 Environment::getSunPosition()
{
	return m_sunPosition;
}