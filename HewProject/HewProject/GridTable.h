#pragma once
#include "CGrid.h"
#include "Vector2.h"
#include "Vector3.h"
#include "CStageMake.h"

#define MAX_GRIDNUM (12)    // グリッドの最大マス数

#define ISOME_FLOOR_SUBPOSY (3.6f)	// アイソメでの隣床のY座標の差（スケールを割る）

// 上から大きい数値にする
#define INFRONT_PLUSZ (0.1f)	// アイソメで1列手前に行くと足されるZ座標
#define ISOME_BACKMOVE (0.001f)	// アイソメの奥に移動するときに使用する
#define HORIZONLINE_PLUSZ (0.0001f)	// 同じ横のラインで右に行くほど足される


// アイソメ用グリッドの盤（テーブル）のクラス
class GridTable
{
	// 一つのマスの大きさ
	Vector3 oneGridScale;

	// [0,0]のグリッドの中心座標(ワールド)
	Vector2 offset;
	float offsetZ;

	// グリッドで
	CGrid::GRID_XY maxGrid;
public:
	// ステージ床の上にあるテーブル
	short int objectTable[MAX_GRIDNUM][MAX_GRIDNUM] = {};

	// ステージ床のテーブル
	short int floorTable[MAX_GRIDNUM][MAX_GRIDNUM] = {};

	GridTable(CGrid::GRID_XY _max, float _scale);

	~GridTable();

	// 指定した座標に何があるか確認する
	int CheckObjectType(CGrid::GRID_XY _gridPos);
	int CheckFloorType(CGrid::GRID_XY _gridPos);

	/// <summary>
	/// グリッドの座標を返す（床と同じ座標）
	/// </summary>
	/// <param name="_gridX">グリッドX座標</param>
	/// <param name="_gridY">グリッドY座標</param>
	/// <returns>ワールド座標</returns>
	Vector3 GridToWorld(CGrid::GRID_XY _pos, CStageMake::BlockType _type);

	Vector3 GetGridScale()const { return oneGridScale; }

	Vector2 GetOffset()const { return offset; }
};

