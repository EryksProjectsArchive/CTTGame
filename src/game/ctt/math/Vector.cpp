//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: math/Vector.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include <math.h>

#include "Vector.h"

Vector3::Vector3()
	: x(0), y(0), z(0)
{
}

Vector3::Vector3(const Vector3& Vector)
	: x(Vector.x), y(Vector.y), z(Vector.z)
{
}

Vector3::Vector3(float fx, float fy, float fz)
	: x(fx), y(fy), z(fz)
{
}

Vector3::~Vector3()
{
}

Vector3 Vector3::operator*(float fRight) const
{
	return Vector3(x * fRight, y * fRight, z * fRight);
}

Vector3 Vector3::operator/(float fRight) const
{
	return Vector3(x / fRight, y / fRight, z / fRight);
}

Vector3 Vector3::operator+(float fRight) const
{
	return Vector3(x + fRight, y + fRight, z + fRight);
}

Vector3 Vector3::operator-(float fRight) const
{
	return Vector3(x - fRight, y - fRight, z - fRight);
}

Vector3 Vector3::operator*(const Vector3& vecRight) const
{
	return Vector3(x * vecRight.x, y * vecRight.y, z * vecRight.z);
}

Vector3 Vector3::operator/(const Vector3& vecRight) const
{
	return Vector3(x / vecRight.x, y / vecRight.y, z / vecRight.z);
}

Vector3 Vector3::operator+(const Vector3& vecRight) const
{
	return Vector3(x + vecRight.x, y + vecRight.y, z + vecRight.z);
}

Vector3 Vector3::operator-(const Vector3& vecRight) const
{
	return Vector3(x - vecRight.x, y - vecRight.y, z - vecRight.z);
}

void Vector3::operator*=(float fRight)
{
	x *= fRight;
	y *= fRight;
	z *= fRight;
}

void Vector3::operator/=(float fRight)
{
	x /= fRight;
	y /= fRight;
	z /= fRight;
}

void Vector3::operator+=(float fRight)
{
	x += fRight;
	y += fRight;
	z += fRight;
}

void Vector3::operator-=(float fRight)
{
	x -= fRight;
	y -= fRight;
	z -= fRight;
}

void Vector3::operator*=(const Vector3& vecRight)
{
	x *= vecRight.x;
	y *= vecRight.y;
	z *= vecRight.z;
}

void Vector3::operator/=(const Vector3& vecRight)
{
	x /= vecRight.x;
	y /= vecRight.y;
	z /= vecRight.z;
}

void Vector3::operator+=(const Vector3& vecRight)
{
	x += vecRight.x;
	y += vecRight.y;
	z += vecRight.z;
}

void Vector3::operator-=(const Vector3& vecRight)
{
	x -= vecRight.x;
	y -= vecRight.y;
	z -= vecRight.z;
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

bool Vector3::operator==(float fRight) const
{
	return (x == fRight) && (y == fRight) && (z == fRight);
}

bool Vector3::operator!=(float fRight) const
{
	return (x != fRight) && (y != fRight) && (z != fRight);
}

bool Vector3::operator==(const Vector3& vecRight) const
{
	return (x == vecRight.x) && (y == vecRight.y) && (z == vecRight.z);
}

bool Vector3::operator!=(const Vector3& vecRight) const
{
	return (x != vecRight.x) && (y != vecRight.y) && (z != vecRight.z);
}

bool Vector3::operator<(const Vector3& vecRight) const
{
	return (x < vecRight.x) && (y < vecRight.y) && (z < vecRight.z);
}

bool Vector3::operator>(const Vector3& vecRight) const
{
	return (x > vecRight.x) && (y > vecRight.y) && (z > vecRight.z);
}

bool Vector3::operator<=(const Vector3& vecRight) const
{
	return (x <= vecRight.x) && (y <= vecRight.y) && (z <= vecRight.z);
}

bool Vector3::operator>=(const Vector3& vecRight) const
{
	return (x >= vecRight.x) && (y >= vecRight.y) && (z >= vecRight.z);
}

Vector3 Vector3::operator=(const Vector3& vecRight)
{
	x = vecRight.x;
	y = vecRight.y;
	z = vecRight.z;
	return *this;
}

Vector3 Vector3::operator=(float fRight)
{
	x = y = z = fRight;
	return *this;
}

float Vector3::operator[](const unsigned int uiIndex)
{
	if (uiIndex>3)
		return 0.0f;

	return *(&x + uiIndex);
}

float Vector3::operator[](const unsigned int uiIndex) const
{
	if (uiIndex>3)
		return 0.0f;

	return *(&x + uiIndex);
}

float Vector3::length() const
{
	return sqrt(x * x + y * y + z * z);
}

float Vector3::dotProduct(const Vector3& vecB) const
{
	return (x * vecB.x + y * vecB.y + z * vecB.z);
}

Vector3 Vector3::crossProduct(const Vector3& vecB) const
{
	Vector3 vec;
	vec.x = y * vecB.z - z * vecB.y;
	vec.y = x * vecB.z - z * vecB.x;
	vec.z = x * vecB.y - y * vecB.x;
	return vec;
}

void Vector3::normalize()
{
	float fNorm = 1.0f / length();
	x *= fNorm;
	y *= fNorm;
	z *= fNorm;
}

Vector3 Vector3::normalized() const
{
	Vector3 vec = Vector3(*this);
	vec.normalize();
	return vec;
}

Vector3 Vector3::lerp(const Vector3& vecStart, const Vector3& vecEnd, float fTime, bool bClampTime)
{
	if (bClampTime)
	{
		if (fTime > 1.0f) fTime = 1.0f;
		if (fTime < 0.0f) fTime = 0.0f;
	}
	return vecStart + (vecEnd - vecStart) * fTime;
}

float Vector3::dotProduct(const Vector3& vecA, const Vector3& vecB)
{
	return vecA.dotProduct(vecB);
}

Vector3 Vector3::crossProduct(const Vector3& vecA, const Vector3& vecB)
{
	return vecA.crossProduct(vecB);
}