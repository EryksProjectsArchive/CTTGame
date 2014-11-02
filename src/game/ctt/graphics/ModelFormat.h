//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/ModelFormat.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

struct string
{
	uint32 len;
	char *value;
};

struct vector
{
	float x;
	float y;
	float z;
};

struct quaternion
{
	float w;
	float x;
	float y;
	float z;
};

struct triangle
{
	uint16 a;
	uint16 b;
	uint16 c;
};

struct vertex
{
	float x;
	float y;
	float z;
	float nx;
	float ny;
	float nz;
	float u;
	float v;
	uint32 color;
	float tanw;
	float tanx;
	float tany;
	float tanz;
};

struct placement
{
	struct vector position;
	struct quaternion rotation;
	struct vector scale;
};

struct aabb
{
	vector min;
	vector max;
};

struct mesh
{
	struct string name;
	uint8 flags;
	aabb simpleColBox;
	struct placement worldPlacement;
	struct string material;
	uint16 verticesCount;
	uint16 trianglesCount;
	struct Vertex3d *vertices;
	struct triangle *triangles;
};

struct mdl
{
	char id[6];
	uint8 version;
	uint8 meshCount;
	struct mesh * meshes;
};

#include <Prerequisites.h>

#include <stdio.h>

class ModelFormat
{
public:
	static bool load(mdl * mdlStruct, File *file);
};