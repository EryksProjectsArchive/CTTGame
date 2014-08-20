//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: math/Matrix.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <math.h>

#include "Vector.h"

class Matrix4x4
{
public:
	// column | row
	float m[4][4];

	Matrix4x4()
	{
		identity();
	}
	
	Matrix4x4(const Matrix4x4 & matrix)
	{
		identity();
		for (unsigned char x = 0; x < 4; ++x)
		{
			for (unsigned char y = 0; y < 4; ++y)
			{
				m[x][y] = matrix.m[x][y];
			}
		}
	}

	~Matrix4x4()
	{

	}

	void translate(float x, float y, float z)
	{
		m[3][0] = x;
		m[3][1] = y;
		m[3][2] = z;
	}

	void translate(const Vector3 translateVector)
	{
		m[3][0] = translateVector.x;
		m[3][1] = translateVector.y;
		m[3][2] = translateVector.z;
	}

	void scale(float x, float y, float z)
	{
		m[0][0] = x;
		m[1][1] = y;
		m[2][2] = z;
	}

	//
	// NOTE: Angle must be passed in radians
	//
	void rotateX(float angle)
	{
		m[1][1] = cosf(angle);
		m[1][2] = sinf(angle);
		
		m[2][1] = -sinf(angle);
		m[2][2] = cosf(angle);
	}

	//
	// NOTE: Angle must be passed in radians
	//
	void rotateY(float angle)
	{
		m[0][0] = cosf(angle);
		m[2][0] = sinf(angle);

		m[0][2] = -sinf(angle);
		m[2][2] = cosf(angle);
	}

	//
	// NOTE: Angle must be passed in radians
	//
	void rotateZ(float angle)
	{
		m[0][0] = cosf(angle);
		m[1][0] = -sinf(angle);

		m[0][1] = sinf(angle);
		m[1][1] = cosf(angle);
	}

	void perspectiveFovLH(float fieldOfView, float screenAspect, float screenNear, float screenDepth)
	{
		m[0][0] = 1.0f / (screenAspect * tan(fieldOfView * 0.5f));
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = 0.0f;

		m[1][0] = 0.0f;
		m[1][1] = 1.0f / tan(fieldOfView * 0.5f);
		m[1][2] = 0.0f;
		m[1][3] = 0.0f;

		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][2] = screenDepth / (screenDepth - screenNear);
		m[2][3] = 1.0f;

		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = -1; // (-screenNear * screenDepth) / (screenDepth - screenNear);
		m[3][3] = 0.0f;
	}

	void perspectiveFovRH(float fieldOfView, float screenAspect, float screenNear, float screenDepth)
	{
		m[0][0] = 1.0f / (screenAspect * tan(fieldOfView * 0.5f));
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = 0.0f;

		m[1][0] = 0.0f;
		m[1][1] = 1.0f / tan(fieldOfView * 0.5f);
		m[1][2] = 0.0f;
		m[1][3] = 0.0f;

		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][2] = screenDepth / (screenDepth - screenNear);
		m[2][3] = 1.0f;

		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 1; // (-screenNear * screenDepth) / (screenDepth - screenNear);
		m[3][3] = 0.0f;
	}

	void lookAt(Vector3 & position, Vector3 & target, Vector3 & up)
	{
		Vector3 zaxis = (position - target).normalized();
		Vector3 xaxis = Vector3::crossProduct(up,zaxis).normalized();
		Vector3 yaxis = Vector3::crossProduct(zaxis, xaxis);

		m[0][0] = xaxis.x;
		m[0][1] = xaxis.y;
		m[0][2] = xaxis.z;
		m[0][2] = -Vector3::dotProduct(xaxis, position);

		m[1][0] = yaxis.x;
		m[1][1] = yaxis.y;
		m[1][2] = yaxis.z;
		m[1][2] = -Vector3::dotProduct(yaxis, position);

		m[2][0] = zaxis.x;
		m[2][1] = zaxis.y;
		m[2][2] = zaxis.z;
		m[2][2] = -Vector3::dotProduct(zaxis, position);

		m[3][0] = 0;
		m[3][1] = 0;
		m[3][2] = 0;
		m[3][2] = 1;
	}

	void identity()
	{
		m[0][0] = 1.0f;
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = 0.0f;

		m[1][0] = 0.0f;
		m[1][1] = 1.0f;
		m[1][2] = 0.0f;
		m[1][3] = 0.0f;

		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][2] = 1.0f;
		m[2][3] = 0.0f;

		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	float & operator()(unsigned char x, unsigned char y)
	{
		return m[x % 4][y % 4];
	}

	Matrix4x4 operator*(Matrix4x4 right) const
	{
		Matrix4x4 matrix;
		matrix.identity();

		matrix(0, 0) = (m[0][0] * right.m[0][0]) + (m[0][1] * right.m[1][0]) + (m[0][2] * right.m[2][0]) + (m[0][3] * right.m[3][0]);
		matrix(0, 1) = (m[0][0] * right.m[0][1]) + (m[0][1] * right.m[1][1]) + (m[0][2] * right.m[2][1]) + (m[0][3] * right.m[3][1]);
		matrix(0, 2) = (m[0][0] * right.m[0][2]) + (m[0][1] * right.m[1][2]) + (m[0][2] * right.m[2][2]) + (m[0][3] * right.m[3][2]);
		matrix(0, 3) = (m[0][0] * right.m[0][3]) + (m[0][1] * right.m[1][3]) + (m[0][2] * right.m[2][3]) + (m[0][3] * right.m[3][3]);

		matrix(1, 0) = (m[1][0] * right.m[0][0]) + (m[1][1] * right.m[1][0]) + (m[1][2] * right.m[2][0]) + (m[1][3] * right.m[3][0]);
		matrix(1, 1) = (m[1][0] * right.m[0][1]) + (m[1][1] * right.m[1][1]) + (m[1][2] * right.m[2][1]) + (m[1][3] * right.m[3][1]);
		matrix(1, 2) = (m[1][0] * right.m[0][2]) + (m[1][1] * right.m[1][2]) + (m[1][2] * right.m[2][2]) + (m[1][3] * right.m[3][2]);
		matrix(1, 3) = (m[1][0] * right.m[0][3]) + (m[1][1] * right.m[1][3]) + (m[1][2] * right.m[2][3]) + (m[1][3] * right.m[3][3]);

		matrix(2, 0) = (m[2][0] * right.m[0][0]) + (m[2][1] * right.m[1][0]) + (m[2][2] * right.m[2][0]) + (m[2][3] * right.m[3][0]);
		matrix(2, 1) = (m[2][0] * right.m[0][1]) + (m[2][1] * right.m[1][1]) + (m[2][2] * right.m[2][1]) + (m[2][3] * right.m[3][1]);
		matrix(2, 2) = (m[2][0] * right.m[0][2]) + (m[2][1] * right.m[1][2]) + (m[2][2] * right.m[2][2]) + (m[2][3] * right.m[3][2]);
		matrix(2, 3) = (m[2][0] * right.m[0][3]) + (m[2][1] * right.m[1][3]) + (m[2][2] * right.m[2][3]) + (m[2][3] * right.m[3][3]);

		matrix(3, 0) = (m[3][0] * right.m[0][0]) + (m[3][1] * right.m[1][0]) + (m[3][2] * right.m[2][0]) + (m[3][3] * right.m[3][0]);
		matrix(3, 1) = (m[3][0] * right.m[0][1]) + (m[3][1] * right.m[1][1]) + (m[3][2] * right.m[2][1]) + (m[3][3] * right.m[3][1]);
		matrix(3, 2) = (m[3][0] * right.m[0][2]) + (m[3][1] * right.m[1][2]) + (m[3][2] * right.m[2][2]) + (m[3][3] * right.m[3][2]);
		matrix(3, 3) = (m[3][0] * right.m[0][3]) + (m[3][1] * right.m[1][3]) + (m[3][2] * right.m[2][3]) + (m[3][3] * right.m[3][3]);
		return matrix;
	}

	operator float*()
	{
		return &m[0][0];
	}
};