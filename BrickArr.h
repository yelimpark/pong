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
	Brick* brickArr[B_ROW][B_COL];

	int CountBrick = B_ROW * B_COL;

	void DeleteBrick(int row, int col);

public:
	BrickArr();

	BRICK_COL_TYPE HanddleCollison(FloatRect fr);

	void Render(RenderWindow& window);

	bool IsBrickCountZero() const;

	~BrickArr();
};

