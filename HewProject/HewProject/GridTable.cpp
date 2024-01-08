#include "GridTable.h"
#include "Vector3.h"
#include "Player.h"

#define OFFSET_Z (0.0f)	// [0,0]の床のz座標


GridTable::GridTable(CGrid::GRID_XY _max, float _scale)
{
	// スケールと最大グリッド数を設定
	oneGridScale = { _scale, _scale, 1.0f };
	maxGrid = _max;

	// [0,0]の床の座標を求める
	offset.x = -oneGridScale.x * (maxGrid.x - 1) / 2.0f;

	// 要調整
	offset.y = -oneGridScale.y / 2.0f;

	offsetZ = OFFSET_Z;
}

GridTable::~GridTable()
{
}

int GridTable::CheckObjectType(CGrid::GRID_XY _gridPos)
{
	return objectTable[_gridPos.y][_gridPos.x];
}

int GridTable::CheckFloorType(CGrid::GRID_XY _gridPos)
{
	return floorTable[_gridPos.y][_gridPos.x];
}

Vector3 GridTable::GridToWorld(CGrid::GRID_XY _grid, CStageMake::BlockType _type)
{
	float disTimes = 0.0f;
	Vector3 floorPos = Vector3::zero;
	floorPos.x = offset.x + (_grid.y + _grid.x) * (oneGridScale.x / 2.0f);
	floorPos.y = offset.y + (_grid.x - _grid.y) * oneGridScale.y / ISOME_FLOOR_SUBPOSY;
	floorPos.z = offsetZ + (_grid.x - _grid.y) * INFRONT_PLUSZ + _grid.x * HORIZONLINE_PLUSZ;

	switch (_type)
	{
	case CStageMake::BlockType::FLOOR:
	{
		return floorPos;
	}
	break;
	case CStageMake::BlockType::WALL:
	case CStageMake::BlockType::CASTELLA:
	case CStageMake::BlockType::BAUMHORIZONTAL:
	case CStageMake::BlockType::BAUMVERTICAL:
	case CStageMake::BlockType::COIN:
	case CStageMake::BlockType::GUMI:
	case CStageMake::BlockType::GALL:
		disTimes = 0.455f;

		break;

	case CStageMake::BlockType::CAKE:
	case CStageMake::BlockType::PROTEIN:
		disTimes = 0.7f;
		break;

	case CStageMake::BlockType::START:
		/*Player::STATE PlayerState = PLAYER->GetPlayerState();
		if (PlayerState == Player::STATE::MUSCLE)
		{
			disTimes = 0.5f * 1.5f;
		}*/
		disTimes = 0.5f;
		break;
	}
	
	Vector3 ret = floorPos;
	ret.y += disTimes * oneGridScale.y;
	ret.z -= 0.01f;

	return ret;
}
