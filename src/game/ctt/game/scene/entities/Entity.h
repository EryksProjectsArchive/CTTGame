//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/scene/entities/Entity.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include <core/DynString.h>

struct EntityType
{
	enum Type
	{
		Dummy,
		Crossroad,
		Box,
		Ball
	};
};

class Entity
{
private:
	EntityType::Type m_type;
public:
	Entity(EntityType::Type type);

	virtual ~Entity();
	virtual EntityType::Type getType();
	virtual void render(RenderContext & ctx);
};