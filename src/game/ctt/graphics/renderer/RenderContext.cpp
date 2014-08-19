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
	: m_shaderProgram(0)
{

}

RenderContext::~RenderContext()
{
	for (auto task : m_renderTasks)
	{
		Renderer::get().setMaterial(task->m_material);
		Renderer::get().renderGeometry(task->m_geometry, task->m_matrix);
		delete task;
	}
	m_renderTasks.clear();
}

RenderTask * RenderContext::newTask()
{
	RenderTask *task = new RenderTask();
	m_renderTasks.pushBack(task);
	return task;
}

void RenderContext::setShaderProgram(ShaderProgram * shaderProgram)
{
	m_shaderProgram = shaderProgram;
}