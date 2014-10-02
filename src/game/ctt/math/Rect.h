//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: math/Rect.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

class Rect
{
public:
	union
	{
		struct
		{
			float top;
			float left;
			float right;
			float bottom;
		};

		struct
		{
			float y;
			float x;
			float x2;
			float y2;
		};
	};

	Rect()
	{
		// Simple 1x1 rect
		top = left = 0;
		right = bottom = 1;
	}

	Rect(float _top, float _left, float _right, float _bottom)
	{
		top = _top;
		left = _left;
		right = _right;
		bottom = _bottom;
	}
};