#pragma once
#include "CObject.h"
#include <iostream>

class CGrid;

// プレイヤー（リス）のオブジェクトクラス
class Player: 
	public CObject
{
	// グリッドクラスのポインタ
	std::shared_ptr<CGrid> grid;

public:
	Player(D3DBUFFER vb, D3DTEXTURE tex);

	void Update() override;
	// プレイヤーが移動する関数(1マスずつ)
	void Move();

	void Draw() override;

	~Player();

	CGrid* GetGrid();
};

