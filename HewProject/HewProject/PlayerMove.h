#pragma once
#include <iostream>

class Player;
class DoTween;

class PlayerMove
{
	std::unique_ptr<Player> player;	// プレイヤークラスのポインタ

	std::unique_ptr<DoTween> dotween;

	//Vector3 target[4] = {};	// 目的座標（上下左右）

	bool isMoving;	// 移動可能フラグ

	float moveTime = 0.0f;	// 仮

public:
	PlayerMove(Player* _p);

	void Update();
	void Move();

	~PlayerMove();
};

