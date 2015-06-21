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

#include <game/scene/entities/Entity.h>
#include <graphics/Model.h>

class CrossroadEntity : public Entity
{
private:
	Model *m_model;
public:
	CrossroadEntity();
	~CrossroadEntity();

	void render(RenderContext & ctx);
	
	void updatePhysics();
};