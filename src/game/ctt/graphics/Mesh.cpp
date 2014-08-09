//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/Mesh.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Mesh.h"

#include "renderer/RenderContext.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::render(RenderContext& context)
{
	Matrix4x4 translationMatrix;
	translationMatrix.translate(m_position);	
	context.push(m_geometry, m_material, &(translationMatrix * m_rotation.toMatrix4x4()));
}