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

#include <graphics/renderer/RenderContext.h>

#include <core/Logger.h>

#include "Entity.h"

uint64 Entity::ms_uid = 0;

Entity::Entity(EntityType::Type type)
	: m_type(type), m_uid(ms_uid++)
{
}

Entity::~Entity()
{

}

EntityType::Type Entity::getType()
{
	return m_type;
}

void Entity::render(RenderContext& ctx)
{
}

uint64 Entity::getUID()
{
	return m_uid;
}