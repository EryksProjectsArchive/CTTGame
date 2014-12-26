//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/renderer/UIRenderContext.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "UIRenderContext.h"
#include "Renderer.h"

UIRenderContext::UIRenderContext()
{
}

UIRenderContext::~UIRenderContext()
{
	for (UIRenderTask* task : m_renderTasks)
	{
		Renderer::get()->setMaterial(task->m_material);
		Renderer::get()->renderGeometry(task->m_geometry);
		delete task;
	}
	m_renderTasks.clear();
}

UIRenderTask * UIRenderContext::newTask()
{
	UIRenderTask *task = new UIRenderTask();
	m_renderTasks.pushBack(task);
	return task;
}