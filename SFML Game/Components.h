#pragma once

#include "Common.h"

// Transform component
//
// Stores the position, velocity, and angle of an Entity
// The angle is how much to rotate the Entity about its center

class CTransform 
{
public:
	Vec2 pos = { 0.0f, 0.0f };
	Vec2 velocity = { 0.0f, 0.0f };
	float angle = 0;

	CTransform(const Vec2 & p, const Vec2 & v, float a)
		: pos(p), velocity(v), angle(a) {}
};

class CShape
{
public:
	sf::CircleShape circle;

	CShape(float radius, int points, const sf::Color& fill, const sf::Color& outline, float thickness)
		: circle(radius, points) 
	{
		circle.setFillColor(fill);
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thickness);
		circle.setOrigin(radius, radius);
	}
};

class CCollision
{
public:
	float radius = 0;

	CCollision(float r)
		: radius(r) {}
};

class CScore
{
public:
	int score = 0;
	CScore(int s)
		: score(s) {}
};

class CLifeSpan
{
public:
	int lifespan = 0;			// number of frames to live
	int frameCreated = 0;				
	
	CLifeSpan(int duration, int created)		
		: lifespan(duration), frameCreated(created) {}
};

class CInput
{
public:
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool leftMouse = false;
	bool rightMouse = false;
	CInput() {}
};