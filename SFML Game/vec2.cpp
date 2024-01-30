#include "Vec2.h"

Vec2::Vec2()
{
}

Vec2::Vec2(float xin, float yin)
	: x(xin),
	y(yin)
{
}

bool Vec2::operator==(const Vec2 & rhs) const
{
	return (x == rhs.x) && (y == rhs.y);
}

bool Vec2::operator != (const Vec2 & rhs) const
{
	return (x != rhs.x) && (y != rhs.y);
}

Vec2 Vec2::operator+(const Vec2 & rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2 & rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(const float val) const
{
	return Vec2(x * val, y * val);
}

Vec2 Vec2::operator/(const float val) const
{
	return Vec2(x / val, y / val);
}

void Vec2::operator+=(const Vec2 & rhs)
{
	x += rhs.x;
	y += rhs.y;
}

void Vec2::operator-=(const Vec2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;

}

void Vec2::operator*=(const float val)
{
	x *= val;
	y *= val;
}

void Vec2::operator/=(const float val)
{
	x /= val;
	y /= val;
}

float Vec2::dist(const Vec2& rhs) const
{
	Vec2 temp = {x - rhs.x, y - rhs.y};

	return std::sqrt(temp.x * temp.x + temp.y * temp.y);
}

void Vec2::normalize()
{
	float L{ std::sqrt(x * x + y * y) };
	x = x / L;
	y = y / L;
}

float Vec2::length() const
{
	return std::sqrt(x * x + y * y);
}

// overload output stream
std::ostream& operator<<(std::ostream& stream, const Vec2& lhs)
{
	return stream << "x: " << lhs.x << " y: " << lhs.y << std::endl;
}