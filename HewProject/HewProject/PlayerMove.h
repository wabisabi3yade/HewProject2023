#pragma once
#include <iostream>
#include "Vector3.h"
#include"DoTween.h"
class Player;
//class DoTween;

class PlayerMove
{

public:
	enum class DIRECTION
	{
		UP,
		DOWN,
		RIGHT,
		LEFT
	};


private:
	std::unique_ptr<Player> player;	// プレイヤークラスのポインタ

	std::unique_ptr<DoTween> dotween;

	DIRECTION direction;

	bool canMoveDir[4];	// 移動可能である方向

	bool isMoving;	// 移動可能フラグ

	bool isMovingLast;

	bool isMovingTrigger;	// isMove = true->falseに変わった瞬間だけtrue

	float moveTime = 0.0f;	// 仮

public:
	PlayerMove(Player* _p);

	void Update();
	void Move(Vector3 _nowpos ,Vector3 _targetpos );
	void MoveAppend(Vector3 _targetPos, float _moveTime, DoTween::FUNC _moveFunc);

	// 移動終えた瞬間に次の移動のための準備をする関数
	void SettingMove();

	~PlayerMove();

	bool GetIsMoving()const { return isMoving; }
	bool GetIsMovingTrrger()const { return isMovingTrigger; }
	DIRECTION GetDirection()const { return direction; }
};

