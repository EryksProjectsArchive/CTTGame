//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: video/Model.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Model.h"

Model::Model()
{
	mMeshesCount = 0;
	mMeshes = 0;
}

Model::~Model()
{

}

void Model::load(const char *fileName)
{

}

void Model::render(IRenderer * renderer)
{
	for (unsigned char i = 0; i < mMeshesCount; i++)
		mMeshes[i]->render(renderer);
}