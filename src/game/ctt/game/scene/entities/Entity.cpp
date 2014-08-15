//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/scene/entities/Entity.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Entity.h"

#include <core/hashing/JenkinsHash.h>
#include <core/Logger.h>

Entity::Entity(String<32> name)
	: m_name(name)
{	
	JenkinsHash hash;
	m_hashedName = hash.encode(m_name, m_name.getLength());

	Debug("entity", "NEW N: %s HN: 0x%X", *m_name, m_hashedName);
}

Entity::~Entity()
{

}

DynString Entity::getName()
{
	return m_name;
}

unsigned int Entity::getHashedName()
{
	return m_hashedName;
}

void Entity::render()
{
	//Info("entity", "render N: %s", *m_name);
}

void Entity::updatePhysics()
{
	//Info("entity", "updatePhysics N: %s", *m_name);
}