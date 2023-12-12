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

	// グリッド座標系
	GRID_XY gridPos;
};

