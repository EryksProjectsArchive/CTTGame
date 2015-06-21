//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: physics/PhysicsWorld.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "PhysicsWorld.h"

#include <core/Timer.h>
#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>

#include <graphics/Camera.h>
#include <graphics/renderer/Renderer.h>
#include <vector>
class PhysicsDebugDrawer : public btIDebugDraw
{
private:
	List<Vertex3d_pc> m_line;
	List<unsigned short> m_indices;
public:
	virtual void	drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
	{
		Vector3 pos = CameraManager::get()->getCurrent()->getPosition();

		Vector3 diffA = pos - Vector3(from.x(), from.y(), from.z());
		Vector3 diffB = pos - Vector3(to.x(), to.y(), to.z());
		if ((glm::length(diffA) > 500) && (glm::length(diffB) > 500))
			return;

		Vertex3d_pc vert;
		vert.x = from.x();
		vert.y = from.y();
		vert.z = from.z();		
		vert.color = 0xFFFFFFFF;// ((uint8)255 << 24) | ((uint8)(color.z() * 255) << 16) | ((uint8)(color.y() * 255) << 8) | ((uint8)(color.x() * 255));
		m_line.pushBack(vert);
		m_indices.pushBack(m_line.size() - 1);
		vert.x = to.x();
		vert.y = to.y();
		vert.z = to.z();
		m_line.pushBack(vert);
		m_indices.pushBack(m_line.size() - 1);
	}

	virtual void	drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color){};

	virtual void	reportErrorWarning(const char* warningString) {};

	virtual void	draw3dText(const btVector3& location, const char* textString) {};

	virtual void	setDebugMode(int debugMode) {};

	virtual int		getDebugMode() const { return DBG_DrawWireframe| DBG_DrawNormals; };

	void doRenderLines()
	{
		Geometry<Vertex3d_pc> geometry;
		Vertex3d_pc *v = new Vertex3d_pc[m_line.size()];
		uint32 vertices = 0;
		while (m_line.size() > 0)
		{
			memcpy(&v[vertices], &m_line.front(), sizeof(Vertex3d_pc));
			m_line.popFront();
			++vertices;
		}
		m_line.clear();
		unsigned short *indices = new unsigned short[m_indices.size()];
		uint32 indices_ = 0;
		while (m_indices.size() > 0)
		{
			indices[indices_] = m_indices.front();
			m_indices.popFront();
			++indices_;
		}
		geometry.fillData(v, vertices, indices, indices_ / 3);
		delete[]v;
		delete[]indices;

		Renderer::get()->renderGeometry(&geometry, glm::mat4());
	}
};

PhysicsWorld::PhysicsWorld()
	: m_dynamicsWorld(0), m_broadphase(0), m_collisionConfiguration(0), m_dispatcher(0), m_solver(0), m_initialized(false), m_debugDrawer(0)
{

}

PhysicsWorld::~PhysicsWorld()
{
	if (m_dynamicsWorld)
	{
		delete m_dynamicsWorld;
		m_dynamicsWorld = 0;
	}

	if (m_broadphase)
	{
		delete m_broadphase;
		m_broadphase = 0;
	}

	if (m_collisionConfiguration)
	{
		delete m_collisionConfiguration;
		m_collisionConfiguration = 0;
	}

	if (m_dispatcher)
	{
		delete m_dispatcher;
		m_dispatcher = 0;
	}

	if (m_solver)
	{
		delete m_solver;
		m_solver = 0;
	}
}

bool PhysicsWorld::init()
{
	if (m_initialized)
		return false;

	//m_debugDrawer = new PhysicsDebugDrawer();

	// Setup bullet
	if (!(m_broadphase = new btDbvtBroadphase()))
	{
		return false;
	}

	if (!(m_collisionConfiguration = new btDefaultCollisionConfiguration()))
	{
		return false;
	}

	if (m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration))
	{
		btGImpactCollisionAlgorithm::registerAlgorithm(m_dispatcher);
	}
	else
	{
		return false;
	}

	if (!(m_solver = new btSequentialImpulseConstraintSolver()))
	{
		return false;
	}

	if (m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration))
	{
		// Set basic world paramters
		m_dynamicsWorld->setGravity(btVector3(0, -10, 0));

		if (m_debugDrawer)
			m_dynamicsWorld->setDebugDrawer(m_debugDrawer);
	}
	else
	{
		return false;
	}


	m_initialized = true;
	return true;
}

void PhysicsWorld::pulse(float dt)
{
	for (PhysicalEntity *entity : m_entities)
		entity->prePhysicsUpdate();

	if (m_dynamicsWorld)
		m_dynamicsWorld->stepSimulation(dt, 10, dt);
	
	for (PhysicalEntity *entity : m_entities)
		entity->postPhysicsUpdate();
}

void PhysicsWorld::render(RenderContext& context)
{
	if (m_debugDrawer)
	{
		m_dynamicsWorld->debugDrawWorld();
		((PhysicsDebugDrawer *)m_debugDrawer)->doRenderLines();
	}
}

void PhysicsWorld::registerEntity(PhysicalEntity * entity)
{
	m_entities.pushBack(entity);
}

void PhysicsWorld::unregisterEntity(PhysicalEntity * entity)
{
	m_entities.remove(entity);
}

void PhysicsWorld::registerRigidBody(btRigidBody *rigidBody)
{
	if (m_dynamicsWorld)
		m_dynamicsWorld->addRigidBody(rigidBody);
}

void PhysicsWorld::unregisterRigidBody(btRigidBody *rigidBody)
{
	if (m_dynamicsWorld)
		m_dynamicsWorld->removeRigidBody(rigidBody);
}

bool PhysicsWorld::rayTest(Vector3 begin, Vector3 end, Vector3 * position, PhysicalEntity ** entity)
{
	if (m_dynamicsWorld)
	{
		btCollisionWorld::ClosestRayResultCallback result(btVector3(begin.x, begin.y, begin.z), btVector3(end.x, end.y, end.z));
		m_dynamicsWorld->rayTest(btVector3(begin.x, begin.y, begin.z), btVector3(end.x, end.y, end.z), result);

		if (result.hasHit())
		{
			position->x = result.m_hitPointWorld.x();
			position->y = result.m_hitPointWorld.y();
			position->z = result.m_hitPointWorld.z();	

			if (entity)
				*entity = (PhysicalEntity *)result.m_collisionObject->getUserPointer();
			return true;
		}
	}
	return false;
}

btDiscreteDynamicsWorld * PhysicsWorld::getDynamicsWorld()
{
	return m_dynamicsWorld;
}