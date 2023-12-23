#pragma once
#include "CObject.h"
#include <iostream>
#include "CGrid.h"


class PlayerMove;

// プレイヤー（リス）のオブジェクトクラス
class Player: 
	public CObject
{
public:
	enum class DIR
	{
		UP,
		DOWN,
		RIGHT,
		LEFT
	};

private:
	std::shared_ptr<PlayerMove> move;

	// グリッドクラスのポインタ
	std::shared_ptr<CGrid> grid;

	int calorie;	// カロリー

	bool canMove;	// 移動可能フラグ

	DIR moveDir;

public:
	Player(D3DBUFFER vb, D3DTEXTURE tex);

	void Update() override;

	void Draw() override;

	~Player();

	CGrid* GetGrid();
};

