#include "BrickArr.h"

BrickArr::BrickArr()
{
	for (int i = 0; i < B_ROW; i++) {
		for (int j = 0; j < B_COL; j++) {
			brickArr[i][j] = new Brick(j * B_WIDTH, i * B_HEIGHT);
		}
	}
}

BRICK_COL_TYPE BrickArr::HanddleCollison(FloatRect fr)
{
	for (int i = 0; i < B_ROW; i++) {
		for (int j = 0; j < B_COL; j++) {
			if (brickArr[i][j] == nullptr) continue;

			FloatRect birickbound = brickArr[i][j]->GetGlobalBounds();
			Vector2f ballPos(fr.left + fr.width * 0.5f, fr.top + fr.height * 0.5);

			if (birickbound.intersects(fr)) {
				DeleteBrick(i, j);
				if (birickbound.left > ballPos.x || birickbound.left + birickbound.width < ballPos.x) {
					return BRICK_COL_TYPE::SIDE;
				}
				else {
					return BRICK_COL_TYPE::TOP_OR_BOTTOM;
				}
			}
		}
	}
	return BRICK_COL_TYPE::NONE;
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

void BrickArr::DeleteBrick(int row, int col)
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
