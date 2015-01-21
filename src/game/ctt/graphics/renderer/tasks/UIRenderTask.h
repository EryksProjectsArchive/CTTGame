//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/renderer/UIRenderTask.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include "BaseRenderTask.h"

#include "../../Geometry.h"

class UIRenderTask : public BaseRenderTask
{
private:
	Geometry<Vertex2d>* m_geometry;
	Material* m_material;

public:
	UIRenderTask()
	{
		m_geometry = 0;
		m_material = 0;
		m_priority = RENDER_LOW_PRIORITY;
	}

	virtual void setGeometry(Geometry<Vertex2d>* geometry)
	{
		m_geometry = geometry;
	}

	virtual void setMaterial(Material* material)
	{
		m_material = material;
	}

	virtual void preformRender(Renderer * renderer)
	{
		renderer->setMaterial(m_material);
		renderer->renderGeometry(m_geometry);
	}
};