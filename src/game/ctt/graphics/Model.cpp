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

Model::Model(FilePath file) : CacheableResource(file)
{
	m_meshesCount = 0;
	m_meshes = 0;
}

Model::~Model()
{
	destroy();
}

void Model::destroy()
{
	if (m_isLoaded)
	{
		if (m_meshes)
		{
			for (unsigned char i = 0; i < m_meshesCount; i++)
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
		FILE *fp = fopen(m_filePath, "rb");

		if (fp)
		{
			mdl mdlData;
			if (ModelFormat::load(&mdlData, fp))
			{
				Debug("model", "Model loaded (%d meshes)", mdlData.meshCount);

				m_meshes = new Mesh*[mdlData.meshCount];
				for (unsigned char i = 0; i < mdlData.meshCount; ++i)
				{
					Debug("model", "Mesh: %s", mdlData.meshes[i].name.value);

					m_meshes[i] = new Mesh(&mdlData.meshes[i]);

					delete[] mdlData.meshes[i].name.value;
					delete[] mdlData.meshes[i].material.value;
					delete[] mdlData.meshes[i].triangles;
					delete[] mdlData.meshes[i].vertices;
				}
				m_meshesCount = mdlData.meshCount;

				delete[] mdlData.meshes;

				m_isLoaded = true;
				return true;
			}
			fclose(fp);			
		}
	}
	return false;
}

void Model::render(RenderContext & renderContext)
{
	for (unsigned char i = 0; i < m_meshesCount; i++)
		m_meshes[i]->render(renderContext);	
}