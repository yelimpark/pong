#include "Brick.h"

Brick::Brick(float x, float y)
	:position(x, y)
{
	shape.setSize(Vector2f(BRICK_WIDTH, BRICK_HEIGHT));
	shape.setPosition(position);
	shape.setFillColor(Color::White);
	shape.setOutlineColor(Color::Black);
	shape.setOutlineThickness(BRICK_OUTLINE);
}

FloatRect Brick::GetGlobalBounds()
{
	return shape.getGlobalBounds();
}

const RectangleShape& Brick::GetShape()
{
	return shape;
}

Vector2f& Brick::GetPos()
{
	return position;
}

Brick::~Brick()
{
}
