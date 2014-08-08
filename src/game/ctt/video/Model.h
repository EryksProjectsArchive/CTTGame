//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: video/Model.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include "renderer/Renderer.h"
#include "Mesh.h"

class Model
{
private:
	unsigned char mMeshesCount;
	Mesh ** mMeshes;
public:
	Model();
	~Model();

	void load(const char *fileName);

	void render(IRenderer * renderer);
};