//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: math/Vector.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

class Vector3
{
public:
	float x, y, z;

	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3& Vector);

	~Vector3();

	// Arithmetical operators
	Vector3 operator*(float) const;
	Vector3 operator/(float) const;
	Vector3 operator+(float) const;
	Vector3 operator-(float) const;

	Vector3 operator*(const Vector3&) const;
	Vector3 operator/(const Vector3&) const;
	Vector3 operator+(const Vector3&) const;
	Vector3 operator-(const Vector3&) const;

	void operator*=(float);
	void operator/=(float);
	void operator+=(float);
	void operator-=(float);

	void operator*=(const Vector3&);
	void operator/=(const Vector3&);
	void operator+=(const Vector3&);
	void operator-=(const Vector3&);

	// Inverse operator
	Vector3 operator-() const;

	// Logical operators
	bool operator==(float) const;
	bool operator!=(float) const;

	bool operator==(const Vector3&) const;
	bool operator!=(const Vector3&) const;

	bool operator<(const Vector3&) const;
	bool operator>(const Vector3&) const;

	bool operator<=(const Vector3&) const;
	bool operator>=(const Vector3&) const;

	// Assign operators
	Vector3 operator=(const Vector3&);
	Vector3 operator=(float);

	// Other operators
	float operator[](const unsigned int);
	float operator[](const unsigned int) const;

	// Other calculations
	float length() const;

	float dotProduct(const Vector3&) const;

	Vector3 crossProduct(const Vector3&) const;

	void normalize();

	Vector3 normalized() const;

	// Interpolations
	static Vector3 lerp(const Vector3&, const Vector3&, float, bool = true);

	// Static methods
	static float dotProduct(const Vector3&, const Vector3&);
	static Vector3 crossProduct(const Vector3&, const Vector3&);
};