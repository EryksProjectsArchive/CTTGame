//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/renderer/RenderContext.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "RenderContext.h"

RenderContext::RenderContext(RenderQueue * queue)
	: m_queue(queue)
{

}

RenderContext::~RenderContext()
{

}

void RenderContext::push(Geometry * geometry, Material *material, Matrix4x4 *matrix)
{
	if (m_queue)
		m_queue->push(geometry, material, matrix);
}