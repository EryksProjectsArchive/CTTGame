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

#include "Model.h"

Model::Model()
{
	m_meshesCount = 0;
	m_meshes = 0;
}

Model::~Model()
{

}

void Model::destroy()
{
	if (m_isLoaded)
	{
		for (unsigned char i = 0; i < m_meshesCount; i++)
		{
			delete m_meshes[i];
		}
		delete m_meshes;
	}
}

bool Model::load(FilePath file)
{
	if (!m_isLoaded)
	{
	
		m_isLoaded = true;
		return true;
	}
	return false;
}

void Model::render(RenderContext & renderContext)
{
	for (unsigned char i = 0; i < m_meshesCount; i++)
		m_meshes[i]->render(renderContext);	
}