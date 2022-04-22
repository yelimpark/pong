#include "Brick.h"

Brick::Brick(float x, float y)
	:position(x, y)
{
	shape.setSize(Vector2f(B_WIDTH, B_HEIGHT));
	shape.setPosition(position);
	shape.setFillColor(Color::White);
	shape.setOutlineColor(Color::Black);
	shape.setOutlineThickness(B_OUTLINE);
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
