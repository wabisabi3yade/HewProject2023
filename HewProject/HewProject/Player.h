#pragma once
#include "CGridObject.h"
#include <iostream>
#include "CGrid.h"
#include "PlayerMove.h"

// プレイヤー（リス）のオブジェクトクラス
class Player :
	public CGridObject
{
public:


	enum class STATE
	{
		NORMAL,	// 通常
		THIN,	// ガリ
		FAT,	// デブ
		MUSCLE,	// マッチョ
		NUM
	};

private:
	std::shared_ptr<PlayerMove> move;

	int calorie;	// カロリー

	int nowFloor;	// 今何層目にいるか

public:

	Player(D3DBUFFER vb, D3DTEXTURE tex);

	void Update() override;

	void Draw() override;

	~Player();

	bool GetIsMoving()const;

	int GetDirection()const;

	PlayerMove* GetPlayerMove()const;
};

