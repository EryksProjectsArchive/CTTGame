//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/environment/Environment.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>
#include <core/Singleton.h>

class Environment : public Singleton < Environment >
{
private:
	glm::vec3 m_sunPosition;

public:
	Environment();
	~Environment();

	void setSunPosition(glm::vec3 position);
	glm::vec3 getSunPosition();
};