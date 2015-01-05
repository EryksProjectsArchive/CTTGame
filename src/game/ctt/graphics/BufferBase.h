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
	uint32 m_bufferId;
	uint32 m_size;
public:
	BufferBase();
	virtual ~BufferBase();

	virtual void allocate(uint32 size, bool dynamic);

	virtual void fillData(void * data);

	friend class Renderer;
	friend class DeferredRendering;
};