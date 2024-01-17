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

Vector3 GridTable::GridToWorld(CGrid::GRID_XY _grid, CGridObject::BlockType _type)
{
	float disTimes = 0.0f;
	Vector3 floorPos = Vector3::zero;
	floorPos.x = offset.x + (_grid.y + _grid.x) * (oneGridScale.x / 2.0f);
	floorPos.y = offset.y + (_grid.x - _grid.y) * oneGridScale.y / ISOME_FLOOR_SUBPOSY;
	// Z座標は[0,0]Z座標を0.0fとし、手前
	floorPos.z = offsetZ + (_grid.x - _grid.y) * INFRONT_PLUSZ + _grid.x * HORIZONLINE_PLUSZ;

	switch (_type)
	{
	case CGridObject::BlockType::FLOOR:
	case CGridObject::BlockType::CASTELLA_FLOOR:
	case CGridObject::BlockType::HOLL:
	case CGridObject::BlockType::WATAAME:
	{
		disTimes = 0.0f;
	}
	break;
	case CGridObject::BlockType::WALL:
	case CGridObject::BlockType::CASTELLA:
	case CGridObject::BlockType::BAUMHORIZONTAL:
	case CGridObject::BlockType::BAUMVERTICAL:
	case CGridObject::BlockType::COIN:
	case CGridObject::BlockType::GUMI:
	case CGridObject::BlockType::GALL:
		disTimes = 0.455f;

		break;

	case CGridObject::BlockType::CAKE:
	case CGridObject::BlockType::PROTEIN:
		disTimes = 0.7f;
		break;

	case CGridObject::BlockType::START:
		/*Player::STATE PlayerState = PLAYER->GetPlayerState();
		if (PlayerState == Player::STATE::MUSCLE)
		{
			disTimes = 0.5f * 1.5f;
		}*/
		disTimes = 0.5f;
		break;
	}

	float floorToMinusZ = 0.0f;
	// タイプからカテゴリを求める
	CGridObject::Category cate =
		static_cast<CGridObject::Category>(CGridObject::TypeToCategory(_type));

	switch (cate)
	{
		// それがアイテムなら
	case CGridObject::Category::ITEM:
		floorToMinusZ = ITEMTOFLOOR_DIS_Z;
		break;
		// それがオブジェクトなら
	case CGridObject::Category::OBJECT:
		floorToMinusZ = OBJTOFLOOR_DIS_Z;
		break;
		// それが床なら
	default:
		break;

	}


	Vector3 ret = floorPos;
	ret.y += disTimes * oneGridScale.y;
	ret.z -= floorToMinusZ;

	return ret;
}

Vector3 GridTable::GridToWorld(CGrid::GRID_XY _grid, CStageMake::BlockType _type)
{
	float disTimes = 0.0f;
	Vector3 floorPos = Vector3::zero;
	floorPos.x = offset.x + (_grid.y + _grid.x) * (oneGridScale.x / 2.0f);
	floorPos.y = offset.y + (_grid.x - _grid.y) * oneGridScale.y / ISOME_FLOOR_SUBPOSY;
	// Z座標は[0,0]Z座標を0.0fとし、手前
	floorPos.z = offsetZ + (_grid.x - _grid.y) * INFRONT_PLUSZ + _grid.x * HORIZONLINE_PLUSZ;

	switch (_type)
	{
	case CStageMake::BlockType::FLOOR:
	case CStageMake::BlockType::CASTELLA_FLOOR:
	case CStageMake::BlockType::HOLL:
	case CStageMake::BlockType::WATAAME:
	{
		disTimes = 0.0f;
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

	float floorToMinusZ = 0.0f;
	// タイプからカテゴリを求める
	CGridObject::Category cate =
		static_cast<CGridObject::Category>(CStageMake::JudgeTypeToCategory(_type));

	switch (cate)
	{
		// それがアイテムなら
	case CGridObject::Category::ITEM:
		floorToMinusZ = ITEMTOFLOOR_DIS_Z;
		break;
		// それがオブジェクトなら
	case CGridObject::Category::OBJECT:
		floorToMinusZ = OBJTOFLOOR_DIS_Z;
		break;
		// それが床なら
	default:
		break;

	}


	Vector3 ret = floorPos;
	ret.y += disTimes * oneGridScale.y;
	ret.z -= floorToMinusZ;

	return ret;
}