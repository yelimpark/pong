#include "Bat.h"

Bat::Bat(float x, float y)
	:originalPosition(x - 500*0.5f, y), position(x - 500 * 0.5f, y)
{
	shape.setSize(Vector2f(500, 5));
	shape.setPosition(position);
	shape.setFillColor(Color::White);
}

FloatRect Bat::GetGlobalBounds()
{
	return shape.getGlobalBounds();
}

const RectangleShape& Bat::GetShape()
{
	return shape;
}

void Bat::SetMoveDir(Sides side)
{
	moveDir = side;
}

void Bat::Update(float dt)
{
	Vector2f dir;

	switch (moveDir)
	{
	case Sides::LEFT:
		dir.x = -1.f;
		break;
	case Sides::RIGHT:
		dir.x = 1.f;
		break;
	case Sides::NONE:
		break;
	default:
		break;
	}

	position += dir * dt * speed;
	shape.setPosition(position);
}

void Bat::InitPos()
{
	position = originalPosition;
}

Bat::~Bat()
{
}
