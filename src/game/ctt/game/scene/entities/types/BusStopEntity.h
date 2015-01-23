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

#include <physics/StaticPhysicalEntity.h>

class BusStopEntity : public Entity, public StaticPhysicalEntity
{
private:
	Model *m_model;
public:
	BusStopEntity();
	~BusStopEntity();

	void render(RenderContext & ctx);
};