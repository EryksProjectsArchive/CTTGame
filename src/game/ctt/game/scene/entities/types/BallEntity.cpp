//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/scene/entities/types/BallEntity.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include <game/Game.h>
#include <game/scene/entities/Entity.h>

#include <graphics/Model.h>

#include <physics/PhysicsWorld.h>
#include <physics/PhysicalEntity.h>

#include "BallEntity.h"

#include <resources/models/ModelLib.h>

BallEntity::BallEntity() : Entity(EntityType::Ball)
{
	m_model = ModelLib::get()->findByName("ball");
	m_model->acquire();

	AABB * aabb = m_model->getAABB();

	float radius = (aabb->getMax().y - aabb->getMin().y) / 2;
	setupPhysics(new btSphereShape(radius));
	setMass(50);
	setFriction(6);
}

BallEntity::~BallEntity()
{
	if (m_model)
		m_model->release();
}

void BallEntity::render(RenderContext & ctx)
{
	if (m_model)
		m_model->render(ctx, m_transform);
}