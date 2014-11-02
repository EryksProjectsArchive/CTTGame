//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/environment/Terrain.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>
#include <graphics/Geometry.h>

#include <btBulletDynamicsCommon.h>

class TerrainGrid
{
private:
	Geometry<Vertex3d> m_geometry;
	Texture* m_texture;
	Material* m_material;

	Matrix4x4 m_world;

	// Next nodes in projected onto 2d plane
	TerrainGrid* m_right;
	TerrainGrid* m_left;
	TerrainGrid* m_top;
	TerrainGrid* m_bottom;

	btRigidBody* m_rigidBody;
public:
	TerrainGrid(Vector3 position, uint32 size);
	~TerrainGrid();

	void render(RenderContext& context);
};

class Terrain
{
private:
	TerrainGrid ***m_node;

	uint32 m_wNodes;
	uint32 m_hNodes;
	uint32 m_width;
	uint32 m_height;
	uint32 m_nodeSize;
public:
	Terrain(uint32 width, uint32 height);
	~Terrain();

	void render(RenderContext& context);
};