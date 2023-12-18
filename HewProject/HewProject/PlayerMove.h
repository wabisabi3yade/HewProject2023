#pragma once
#include <iostream>

class Player;
class DoTween;

class PlayerMove
{
	std::unique_ptr<Player> player;	// プレイヤークラスのポインタ

	std::unique_ptr<DoTween> dotween;

	bool isMoving;	// 移動可能フラグ

public:
	PlayerMove(Player* _p);

	void Update();
	void Move();

	~PlayerMove();
};

