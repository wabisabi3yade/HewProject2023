#pragma once

#include"Vector2.h"

// グリッド（マス目）に関してのクラス
class CGrid
{
public:
	struct GRID_XY
	{
		int x, y;
	};

private:
	GRID_XY gridPos;

public:
	// グリッド座標に代入する
	void SetGridPos(Vector2 _p);
	GRID_XY GetGridPos()const { return gridPos; }
};

