#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball {
private:
	Vector2f position;
	RectangleShape shape;
	Vector2f originalPosition;

	float speed = 1000.f;
	Vector2f dir;

public:
	Ball(float x, float y);

	FloatRect GetGlobalBounds();

	const RectangleShape& GetShape();

	void ReboundsSides();

	void ReboundBatorTop();

	void ReboundBottom();

	void Init();

	void Update(float dt);

};