//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/Model.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include <stdio.h>

#include <core/Logger.h>

#include "Model.h"
#include "ModelFormat.h"

#include <io/fs/FileSystem.h>

Model::Model(const DynString name, FilePath file) 
	: CacheableResource(file),
	  m_meshes(0),
	  m_name(name),
	  m_meshesCount(0)
{
}

Model::~Model()
{
}

void Model::destroy()
{
	if (m_isLoaded)
	{
		if (m_meshes)
		{
			for (unsigned char i = 0; i < m_meshesCount; ++i)
			{
				if (m_meshes[i])
				{
					delete m_meshes[i];
					m_meshes[i] = 0;
				}
			}
			delete[] m_meshes;
			m_meshes = 0;
		}
		m_isLoaded = false;
	}
}

bool Model::load()
{
	if (!m_isLoaded)
	{
		File *file = FileSystem::get()->open(m_filePath, FileOpenMode::Read | FileOpenMode::Binary);
		if (file->isLoaded())
		{
			Vector3 max, min;
			mdl mdlData;
			if (ModelFormat::load(&mdlData, file))
			{
				m_meshes = new Mesh*[mdlData.meshCount];
				for (unsigned char i = 0; i < mdlData.meshCount; ++i)
				{
					m_meshes[i] = new Mesh(&mdlData.meshes[i]);

					// Update model AABB
					AABB *aabb = m_meshes[i]->getAABB();
					if (aabb)
					{
						float axis = aabb->getMin().x;
						if (axis < min.x)
							min.x = axis;

						axis = aabb->getMin().y;
						if (axis < min.y)
							min.y = axis;

						axis = aabb->getMin().z;
						if (axis < min.z)
							min.z = axis;

						axis = aabb->getMax().x;
						if (axis > max.x)
							max.x = axis;

						axis = aabb->getMax().y;
						if (axis > max.y)
							max.y = axis;

						axis = aabb->getMax().z;
						if (axis > max.z)
							max.z = axis;
					}

					delete[] mdlData.meshes[i].name.value;
					delete[] mdlData.meshes[i].material.value;
					delete[] mdlData.meshes[i].triangles;
					delete[] mdlData.meshes[i].vertices;
				}
				m_meshesCount = mdlData.meshCount;
				
				// Update aabb
				m_aabb.set(min, max);

				delete[] mdlData.meshes;

				m_isLoaded = true;		
			}

			FileSystem::get()->close(file);
			return m_isLoaded;
		}
	}
	return false;
}

void Model::setMatrix(const Matrix4x4 matrix)
{
	m_matrix = matrix;
}

void Model::render(RenderContext & renderContext)
{
	for (unsigned char i = 0; i < m_meshesCount; ++i)
		m_meshes[i]->render(renderContext, m_matrix);	
}

AABB * Model::getAABB()
{
	return &m_aabb;
}