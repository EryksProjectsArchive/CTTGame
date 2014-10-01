//////////////////////////////////////////////
//
//         City Transport Tycoon
//     Copyright (C) Black Ice Mountains
//          All rights reserved
//
// File     : math/AABB.h
// Author   : Eryk Dwornicki      
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

class AABB
{
private:
	Vector3 m_min;
	Vector3 m_max;

public:
	AABB()
	{

	}

	AABB(Vector3 min, Vector3 max)
	{
		m_min = min;
		m_max = max;
	}

	void set(Vector3 min, Vector3 max)
	{
		m_min = min;
		m_max = max;
	}

	const Vector3 getMin()
	{
		return m_min;
	}

	const Vector3 getMax()
	{
		return m_max;
	}

	AABB& operator=(const AABB& rhs)
	{
		m_min = rhs.m_min;
		m_max = rhs.m_max;
		return *this;
	}
};