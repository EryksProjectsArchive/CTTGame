//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/renderer/RenderContext.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include "RenderQueue.h"
#include <graphics/Geometry.h>
#include <graphics/Material.h>

#include <math/Matrix.h>

class RenderContext
{
private:
	RenderQueue * m_queue;
public:
	RenderContext(RenderQueue * queue);
	~RenderContext();

	void push(Geometry * geometry, Material *material, Matrix4x4 *matrix);
};