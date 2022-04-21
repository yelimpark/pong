#pragma once
#include "Brick.h"

class BrickArr
{
private:
	Brick* brickArr[B_ROW][B_COL];

	int CountBrick = B_ROW * B_COL;

	void DeleteBrick(int col, int row);

public:
	BrickArr();

	bool HanddleCollison(FloatRect fr);

	void Render(RenderWindow& window);

	bool IsBrickCountZero() const;

	~BrickArr();
};

