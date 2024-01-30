#pragma once

#include "Common.h"

// Vector class responsible for 2D vector math
class Vec2
{
public:
	float x = 0;
	float y = 0;

	Vec2();
	Vec2(float xin, float yin);

	bool operator == (const Vec2& rhs) const;
	bool operator != (const Vec2& rhs) const;

	Vec2 operator + (const Vec2& rhs) const;
	Vec2 operator - (const Vec2& rhs) const;
	Vec2 operator / (const float val) const;
	Vec2 operator * (const float val) const;

	void operator += (const Vec2& rhs);
	void operator -= (const Vec2& rhs);
	void operator /= (const float val);
	void operator *= (const float val);

	float dist(const Vec2& rhs) const;	// return the distance between two vectors
	void normalize();					// normalize the created vector
	float length() const;				// calculate length of the vector

};