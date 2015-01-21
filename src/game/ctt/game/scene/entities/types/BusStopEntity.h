//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/scene/entities/types/BusStopEntity.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include <physics/DynamicPhysicalEntity.h>

class BusStopEntity : public Entity, public DynamicPhysicalEntity
{
private:
	Model *m_model;
public:
	BusStopEntity();
	~BusStopEntity();

	void render(RenderContext & ctx);
};