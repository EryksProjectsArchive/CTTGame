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

#include <Prerequisites.h>

#include <graphics/Geometry.h>
#include <graphics/Material.h>

#include <core/List.h>
#include <core/SharedPtr.h>

#include "tasks/BaseRenderTask.h"

class ShaderProgram;
class RenderContext
{
private:
	List<BaseRenderTask *> m_task[RENDER_PRIORITY_COUNT];
public:
	RenderContext();
	~RenderContext();

	template <typename taskType>
	taskType* newTask()
	{
		taskType *task = new taskType();

		RenderPriority priority = task->getRenderPriority();
		switch (priority)
		{
		case RENDER_HIGH_PRIORITY:
			{
				m_task[priority].pushFront(task);
			} break;
		case RENDER_LOW_PRIORITY:
			{
				m_task[priority].pushBack(task);
			} break;
		default:
			{
				m_task[priority].pushBack(task);
			} break;
		}		
		return task;
	}
};