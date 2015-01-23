//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/renderer/BaseRenderTask.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include "../RenderPriority.h"

class BaseRenderTask
{
protected:
	RenderPriority m_priority;
public:
	BaseRenderTask()
	{
		m_priority = RENDER_NORMAL_PRIORITY;
	}

	virtual ~BaseRenderTask() {}

	virtual RenderPriority getRenderPriority()
	{
		return m_priority;
	}

	virtual void performRender(class Renderer* renderer) = 0;

	friend class RenderContext;
};