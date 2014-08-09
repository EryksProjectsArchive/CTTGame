//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: math/Quaternion.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include "Matrix.h"

class Quaternion
{
public:
	float w, x, y, z;

	Quaternion()
	{
		x = y = z = 0;
		w = 1;
	}

	/**
	 *	NOTE: There may be issue (we should use 3x3 matrix for it)
	 *  Based on: http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/
	 */
	Matrix4x4 toMatrix4x4(Matrix4x4 result = Matrix4x4())
	{
		result(0, 0) = 1 - 2 * (y*y) - 2 * (z*z);
		result(0, 1) = 2 * x * y + 2 * z * w;
		result(0, 2) = 2 * x * z - 2 * y * w;

		result(1, 0) = 2 * x * y - 2 * z * w;
		result(1, 1) = 1 - 2 * (x*x) - 2 * (z*z);
		result(1, 2) = 2 * y * z + 2 * x * w;

		result(2, 0) = 2 * x * z + 2 * y * w;
		result(2, 1) = 2 * y * z - 2 * x * w;
		result(2, 2) = 1 - 2 * (x*x) - 2 * (y*y);

		return result;
	}
};