//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/renderer/ModelRenderTask.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include "BaseRenderTask.h"

#include "../../Geometry.h"

class ModelRenderTask : public BaseRenderTask
{
private:
	Geometry<Vertex3d> * m_geometry;
	Material * m_material;
	Matrix4x4 m_matrix;

public:
	ModelRenderTask()
	{
		m_geometry = 0;
		m_material = 0;
	}

	~ModelRenderTask()
	{
		if (m_material)
			m_material->release();
	}

	virtual void setGeometry(Geometry<Vertex3d> *geometry)
	{
		m_geometry = geometry;
	}

	virtual void setMaterial(Material* material)
	{
		m_material = material;
		m_material->acquire();
	}

	virtual void setModelMatrix(const Matrix4x4& matrix)
	{
		m_matrix = matrix;
	}

	virtual void performRender(Renderer * renderer)
	{
		renderer->setMaterial(m_material);
		renderer->renderGeometry(m_geometry, m_matrix);
	}
};