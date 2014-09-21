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

class RenderTask
{
public:
	Geometry * m_geometry;
	SharedPtr<Material> m_material;
	Matrix4x4 m_matrix;

	RenderTask()
	{
		m_geometry = 0;
	}
};

class ShaderProgram;
class RenderContext
{
private:
	ShaderProgram *m_shaderProgram;

	List<RenderTask *> m_renderTasks;
public:
	RenderContext();
	~RenderContext();

	RenderTask * newTask();

	void setShaderProgram(ShaderProgram *shaderProgram);
};