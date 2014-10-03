//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/scene/entities/types/CrossroadEntity.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include <physics/PhysicsWorld.h>
#include <physics/PhysicalEntity.h>

class CrossroadEntity : public Entity, public PhysicalEntity
{
private:
	Model *m_model;
public:
	CrossroadEntity();
	~CrossroadEntity();

	void render(RenderContext & ctx);

	void prePhysicsUpdate() override;
	void postPhysicsUpdate() override;
};