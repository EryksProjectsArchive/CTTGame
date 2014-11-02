//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/renderer/UIRenderContext.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include <graphics/Geometry.h>
#include <graphics/Material.h>

#include <core/List.h>
#include <core/SharedPtr.h>

struct Vertex2d;
class UIRenderTask
{
public:
	Geometry<Vertex2d>* m_geometry;
	Material* m_material;

	UIRenderTask()
	{
		m_geometry = 0;
		m_material = 0;
	}
};

class ShaderProgram;
class UIRenderContext
{
private:
	List<UIRenderTask*> m_renderTasks;
public:
	UIRenderContext();
	~UIRenderContext();

	UIRenderTask* newTask();
};