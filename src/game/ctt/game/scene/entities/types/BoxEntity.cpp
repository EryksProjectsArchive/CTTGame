//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/scene/entities/types/BoxEntity.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include <game/scene/entities/Entity.h>

#include <graphics/Model.h>

#include "BoxEntity.h"

#include <resources/models/ModelLib.h>

BoxEntity::BoxEntity()
	: Entity(EntityType::Box), m_model(0)
{
	m_model = ModelLib::get()->findByName("box");
	if (m_model)
	{
		m_model->acquire();

		// Setup physics
		AABB * aabb = m_model->getAABB();
		setupPhysics(new btBoxShape(btVector3((aabb->getMax().x - aabb->getMin().x) / 2, (aabb->getMax().y - aabb->getMin().y) / 2, (aabb->getMax().z - aabb->getMin().z) / 2)));
		setMass(5.0f);
		setFriction(100.0f);
	}
}

BoxEntity::~BoxEntity()
{
	if (m_model)
		m_model->release();
}

void BoxEntity::render(RenderContext & ctx)
{
	if (m_model)
		m_model->render(ctx, m_transform);
}