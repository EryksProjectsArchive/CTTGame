//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/BufferBase.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

struct BufferType
{
	enum Type
	{
		VERTEX = 1,
		INDEX = 2
	};
};

class BufferBase
{
protected:
	bool m_isDynamic;
	unsigned int m_bufferId;
	unsigned int m_size;
public:
	BufferBase();
	virtual ~BufferBase();

	virtual void allocate(unsigned int size, bool dynamic);

	virtual void fillData(void * data);

	friend class Renderer;
};