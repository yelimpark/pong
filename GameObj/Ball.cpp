#include "Ball.h"
#include <cmath>

Ball::Ball(float x, float y) : originalPosition(x, y), position(x,y)
{
	dir.x = 1.f;
	dir.y = 1.f;

	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
	dir.x /= length;
	dir.y /= length;

	shape.setSize(Vector2f(10, 10));
	shape.setPosition(position);
	shape.setFillColor(Color::White);
}

FloatRect Ball::GetGlobalBounds()
{
	return shape.getGlobalBounds();
}

const RectangleShape& Ball::GetShape()
{
	return shape;
}

void Ball::ReboundsSides()
{
	dir.x *= -1.f;
}

void Ball::ReboundBatorTop()
{
	dir.y *= -1.f;
}

void Ball::ReboundBottom()
{
	position = originalPosition;
}

void Ball::Init()
{
	dir.x = 1.f;
	dir.y = 1.f;

	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
	dir.x /= length;
	dir.y /= length;

	position = originalPosition;
}

void Ball::Update(float dt)
{
	position += dir * dt * speed;
	shape.setPosition(position);
}
