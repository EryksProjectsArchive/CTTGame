//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/renderer/RenderQueue.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

class Geometry;
class Material;
class Matrix4x4;

class RenderQueue
{
private:
	
public:
	RenderQueue();
	~RenderQueue();

	void push(Geometry * geometry, Material *material, Matrix4x4 *matrix);
};
