//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/scene/entities/types/CrossroadEntity.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "CrossroadEntity.h"

CrossroadEntity::CrossroadEntity()
	: Entity("CrossroadEntity")
{
	m_model = new Model("../../data/models/road.mdl");
	m_model->acquire();
}

CrossroadEntity::~CrossroadEntity()
{
	if (m_model)
	{
		m_model->free();
		delete m_model;
		m_model = 0;
	}
}

void CrossroadEntity::render(RenderContext & ctx)
{
	if (m_model)
		m_model->render(ctx);
}

void CrossroadEntity::updatePhysics()
{

}