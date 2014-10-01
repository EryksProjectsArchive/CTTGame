//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/scene/entities/types/BallEntity.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include <physics/PhysicsWorld.h>
#include <physics/PhysicalEntity.h>

class BallEntity : public Entity, public PhysicalEntity
{
private:
	Model *m_model;
public:
	BallEntity();
	~BallEntity();

	void render(RenderContext & ctx);

	void prePhysicsUpdate() override;
	void postPhysicsUpdate() override;
};