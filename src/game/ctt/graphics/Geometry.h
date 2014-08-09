//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/Geometry.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include "renderer/BufferBase.h"

class Geometry
{
private:
	BufferBase* m_vertexBuffer;
	BufferBase* m_indexBuffer;

public:
	Geometry();
	~Geometry();
};