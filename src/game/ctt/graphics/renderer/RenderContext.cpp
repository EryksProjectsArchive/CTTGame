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
#include "Renderer.h"

RenderContext::RenderContext()
{
}

RenderContext::~RenderContext()
{
	Renderer * renderer = Renderer::get();
	for (uint32 i = 0; i < RENDER_PRIORITY_COUNT; ++i)
	{
		while (m_task[i].size() > 0)
		{
			BaseRenderTask *task = m_task[i].front();
			if (task)
			{
				task->performRender(renderer);
				delete task;
			}
			m_task[i].popFront();
		}
	}
}
