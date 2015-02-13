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
#include "../../ui/UISkin.h"

class UIRenderTask : public BaseRenderTask
{
protected:
	Geometry<Vertex2d>* m_geometry;
	UI::Skin* m_skin;
public:
	UIRenderTask()
	{
		m_geometry = 0;
		m_priority = RENDER_LOW_PRIORITY;
		m_skin = 0;
	}

	virtual ~UIRenderTask() 
	{
		if (m_geometry)
		{
			delete m_geometry;
			m_geometry = 0;
		}
	}

	virtual void setSkin(UI::Skin * skin)
	{
		m_skin = skin;
	}

	virtual void setGeometry(Geometry<Vertex2d>* geometry)
	{
		m_geometry = geometry;
	}

	virtual void preformRender(Renderer * renderer)
	{
		if (m_skin)
		{
			renderer->setMaterial(m_skin->getMaterial());
			renderer->renderGeometry(m_geometry);
		}
		else
		{
			Warning("UIRenderTask", "Unable to preform render task. No skin set.");
		}
	}
};