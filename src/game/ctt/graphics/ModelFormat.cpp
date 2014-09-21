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

bool ModelFormat::load(mdl * mdlStruct, FILE * fp)
{
	if (!mdlStruct || !fp)
		return false;


	fread(mdlStruct, sizeof(mdl) - sizeof(mdlStruct->meshes), 1, fp);

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
		fread(&mdlStruct->meshes[i].name.len, sizeof(mdlStruct->meshes[i].name.len), 1, fp);
		mdlStruct->meshes[i].name.value = new char[mdlStruct->meshes[i].name.len+1];
		fread(mdlStruct->meshes[i].name.value, sizeof(char), mdlStruct->meshes[i].name.len, fp);
		mdlStruct->meshes[i].name.value[mdlStruct->meshes[i].name.len] = '\0';
		
		// Read flags and world placement
		fread(&mdlStruct->meshes[i].flags, sizeof(mdlStruct->meshes[i].flags), 1, fp);
		fread(&mdlStruct->meshes[i].worldPlacement, sizeof(mdlStruct->meshes[i].worldPlacement), 1, fp);
		
		// Read material name
		fread(&mdlStruct->meshes[i].material.len, sizeof(mdlStruct->meshes[i].material.len), 1, fp);
		mdlStruct->meshes[i].material.value = new char[mdlStruct->meshes[i].material.len+1];
		fread(mdlStruct->meshes[i].material.value, sizeof(char), mdlStruct->meshes[i].material.len, fp);
		mdlStruct->meshes[i].material.value [mdlStruct->meshes[i].material.len] = '\0';
		
		// Read vertices count and triangles count
		fread(&mdlStruct->meshes[i].verticesCount, sizeof(mdlStruct->meshes[i].verticesCount) + sizeof(mdlStruct->meshes[i].trianglesCount), 1, fp);
		
		// xx 00 (vertices Count)
		// 00 00 (triangles count)
		mdlStruct->meshes[i].vertices = new vertex[mdlStruct->meshes[i].verticesCount];
		fread(mdlStruct->meshes[i].vertices, sizeof(vertex), mdlStruct->meshes[i].verticesCount, fp);
		
		mdlStruct->meshes[i].triangles = new triangle[mdlStruct->meshes[i].trianglesCount];
		fread(mdlStruct->meshes[i].triangles, sizeof(triangle), mdlStruct->meshes[i].trianglesCount, fp);

		//Debug("ModelFormat", "Mesh %s (Tris: %d, Verts: %d)", mdlStruct->meshes[i].name.value, mdlStruct->meshes[i].trianglesCount, mdlStruct->meshes[i].verticesCount);
	}
	return true;
}