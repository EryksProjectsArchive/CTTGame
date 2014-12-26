//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/scene/entities/types/BoxEntity.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include <physics/DynamicPhysicalEntity.h>

class BoxEntity : public Entity, public DynamicPhysicalEntity
{
private:
	Model *m_model;
public:
	BoxEntity();
	~BoxEntity();

	void render(RenderContext & ctx);
};