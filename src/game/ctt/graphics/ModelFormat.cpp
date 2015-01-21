//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/ModelFormat.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "ModelFormat.h"

#include <cstring>
#include <core/Logger.h>

#include <io/fs/FileSystem.h>

#include "Vertex3d.h"

bool ModelFormat::load(mdl * mdlStruct, File *file)
{
	if (!mdlStruct || !file || !file->isLoaded())
		return false;


	file->read(mdlStruct, 1, sizeof(mdl) - sizeof(mdlStruct->meshes));

	if (memcmp(mdlStruct->id, "CTTMDL", 6) != 0)
	{
		Error("ModelFormat", "File id does not match\n.");
		return false;
	}

	if (mdlStruct->version != 1)
	{
		Error("ModelFormat", "File version does not match\n.");
		return false;
	}

	mdlStruct->meshes = new mesh[mdlStruct->meshCount];

	for (unsigned char i = 0; i < mdlStruct->meshCount; ++i)
	{
		// Read name
		file->read(&mdlStruct->meshes[i].name.len, 1, sizeof(mdlStruct->meshes[i].name.len));
		mdlStruct->meshes[i].name.value = new char[mdlStruct->meshes[i].name.len+1];
		file->read(mdlStruct->meshes[i].name.value, mdlStruct->meshes[i].name.len, sizeof(char));
		mdlStruct->meshes[i].name.value[mdlStruct->meshes[i].name.len] = '\0';
		
		// Read flags and world placement
		file->read(&mdlStruct->meshes[i].flags, 1, sizeof(mdlStruct->meshes[i].flags));
		file->read(&mdlStruct->meshes[i].simpleColBox, 1, sizeof(mdlStruct->meshes[i].simpleColBox));
		file->read(&mdlStruct->meshes[i].worldPlacement, 1, sizeof(mdlStruct->meshes[i].worldPlacement));
		
		// Read material name
		file->read(&mdlStruct->meshes[i].material.len, 1, sizeof(mdlStruct->meshes[i].material.len));
		
		mdlStruct->meshes[i].material.value = new char[mdlStruct->meshes[i].material.len+1];
		file->read(mdlStruct->meshes[i].material.value, mdlStruct->meshes[i].material.len, sizeof(char));
		mdlStruct->meshes[i].material.value [mdlStruct->meshes[i].material.len] = '\0';
		
		// Read vertices count and triangles count
		file->read(&mdlStruct->meshes[i].verticesCount, 1, sizeof(mdlStruct->meshes[i].verticesCount) + sizeof(mdlStruct->meshes[i].trianglesCount));
		
		// xx 00 (vertices Count)
		// 00 00 (triangles count)
		mdlStruct->meshes[i].vertices = new Vertex3d[mdlStruct->meshes[i].verticesCount];
		file->read(mdlStruct->meshes[i].vertices, mdlStruct->meshes[i].verticesCount, sizeof(vertex));
		
		mdlStruct->meshes[i].triangles = new triangle[mdlStruct->meshes[i].trianglesCount];
		file->read(mdlStruct->meshes[i].triangles, mdlStruct->meshes[i].trianglesCount, sizeof(triangle));

		//Debug("ModelFormat", "Mesh %s (Tris: %d, Verts: %d)", mdlStruct->meshes[i].name.value, mdlStruct->meshes[i].trianglesCount, mdlStruct->meshes[i].verticesCount);
	}
	return true;
}