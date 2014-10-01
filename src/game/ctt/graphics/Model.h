//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/Model.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include <resources/CacheableResource.h>
#include "Mesh.h"

class Model : public CacheableResource
{
private:
	unsigned char m_meshesCount;
	Mesh** m_meshes;

	AABB m_aabb;

	Matrix4x4 m_matrix;
public:
	Model(FilePath file);
	~Model() override;
	
	void destroy() override;
	bool load() override;

	void render(RenderContext& renderContext);

	void setMatrix(const Matrix4x4 matrix);

	AABB * getAABB();
};