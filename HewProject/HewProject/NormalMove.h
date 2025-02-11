#pragma once
#include "PlayerMove.h"

class NormalMove :
	public PlayerMove
{
public:
	NormalMove(Player* _p);

	// 移動関数
	void Move(DIRECTION _dir) override;

	// どの方向に移動ができるか取得する関数
	void  CheckCanMove() override;

	~NormalMove();
};
