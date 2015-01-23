//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/scene/entities/types/BusStopEntity.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include <game/scene/entities/Entity.h>

#include <graphics/Model.h>

#include "BusStopEntity.h"

#include <resources/models/ModelLib.h>

BusStopEntity::BusStopEntity()
	: Entity(EntityType::BusStop), m_model(0)
{
	m_model = ModelLib::get()->findByName("busstop_lvl1");
	if (m_model)
	{
		m_model->acquire();

		// Setup physics
		AABB * aabb = m_model->getAABB();
		setupPhysics(new btBoxShape(btVector3((aabb->getMax().x - aabb->getMin().x)/2, (aabb->getMax().y - aabb->getMin().y)/2, (aabb->getMax().z - aabb->getMin().z)/2)));
		//setMass(5.0f);
		setFriction(100.0f);
	}
}

BusStopEntity::~BusStopEntity()
{
	if (m_model)
		m_model->release();
}

void BusStopEntity::render(RenderContext & ctx)
{
	if (m_model)
		m_model->render(ctx, m_transform);
}