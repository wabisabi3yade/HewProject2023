#include "CGrid.h"

Vector2 CGrid::GridToWorldPos()
{
	return Vector2();
}

void CGrid::SetGridPos(Vector2 _p)
{
	// float型をintに変換する
	int x = (int)_p.x;
	int y = (int)_p.y;

	// グリッド座標に代入する
	gridPos = { x, y };
}
