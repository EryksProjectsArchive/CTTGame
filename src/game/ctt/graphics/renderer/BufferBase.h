//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/renderer/BufferBase.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

enum BufferType
{
	BUFFER_TYPE_VERTEX = 1,
	BUFFER_TYPE_INDEX = 2
};

class BufferBase
{
public:
	BufferBase();
	~BufferBase();

	virtual void allocate(unsigned int size);

	virtual void fillData(void * data);
};