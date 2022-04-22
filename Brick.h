#pragma once
#include "Macro.h"

#include <SFML/Graphics.hpp>

using namespace sf;

class Brick
{
private:
	Vector2f position;

	RectangleShape shape;

public:
	Brick(float x, float y);

	FloatRect GetGlobalBounds();

	const RectangleShape& GetShape();

	Vector2f& GetPos();

	~Brick();
};

