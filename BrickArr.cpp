#include "BrickArr.h"

BrickArr::BrickArr()
{
	for (int i = 0; i < B_ROW; i++) {
		for (int j = 0; j < B_COL; j++) {
			brickArr[i][j] = new Brick(j * B_WIDTH, i * B_HEIGHT);
		}
	}
}

bool BrickArr::HanddleCollison(FloatRect fr)
{
	for (int i = 0; i < B_ROW; i++) {
		for (int j = 0; j < B_COL; j++) {
			if (brickArr[i][j] != nullptr && fr.intersects(brickArr[i][j]->GetGlobalBounds())) {
				DeleteBrick(j, i);
				return true;
			}
		}
	}
	return false;
}

void BrickArr::Render(RenderWindow& window)
{
	for (int i = 0; i < B_ROW; i++) {
		for (int j = 0; j < B_COL; j++) {
			if (brickArr[i][j] != nullptr)
				window.draw(brickArr[i][j]->GetShape());
		}
	}
}

bool BrickArr::IsBrickCountZero() const
{
	return (CountBrick == 0);
}

void BrickArr::DeleteBrick(int col, int row)
{
	if (brickArr[row][col] == nullptr) return;
	delete brickArr[row][col];
	brickArr[row][col] = nullptr;
	CountBrick--;
}

BrickArr::~BrickArr()
{
	for (int i = 0; i < B_ROW; i++) {
		for (int j = 0; j < B_COL; j++) {
			delete brickArr[i][j];
		}
	}
}
