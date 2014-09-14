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

struct string
{
	unsigned int len;
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
	unsigned short a;
	unsigned short b;
	unsigned short c;
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
	float color_r;
	float color_g;
	float color_b;
	float color_a;
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


struct mesh
{
	struct string name;
	unsigned char flags;
	struct placement worldPlacement;
	struct string material;
	unsigned short verticesCount;
	unsigned short trianglesCount;
	struct vertex *vertices;
	struct triangle *triangles;
};

struct mdl
{
	char id[6];
	unsigned char version;
	unsigned char meshCount;
	struct mesh * meshes;
};

#include <Prerequisites.h>

#include <stdio.h>

class ModelFormat
{
public:
	static bool load(mdl * mdlStruct, FILE * fp);
};