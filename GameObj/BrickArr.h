#pragma once
#include "Brick.h"

enum class BRICK_COL_TYPE {
	SIDE,
	TOP_OR_BOTTOM,
	NONE
};

class BrickArr
{
private:
	Brick* brickArr[BRICK_ROW][BRICK_COL];

	int CountBrick = BRICK_ROW * BRICK_COL;

	void DeleteBrick(int row, int col);

public:
	BrickArr();

	BRICK_COL_TYPE HanddleCollison(FloatRect fr);

	void Render(RenderWindow& window);

	bool IsBrickCountZero() const;

	~BrickArr();
};

