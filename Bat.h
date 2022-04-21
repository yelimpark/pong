#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

enum class Sides {
	LEFT,
	RIGHT,
	NONE
};

class Bat {
private:
	Vector2f position;

	Vector2f originalPosition;

	RectangleShape shape;

	float speed = 1000.f;

	Sides moveDir = Sides::NONE;

public:
	Bat(float x, float y);

	FloatRect GetGlobalBounds();

	const RectangleShape& GetShape();

	void SetMoveDir(Sides side);

	void Update(float dt);

	void InitPos();

	~Bat();
};