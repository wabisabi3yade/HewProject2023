#pragma once
#include <iostream>
#include "Vector3.h"

class Player;
class DoTween;

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
	std::unique_ptr<Player> player;	// �v���C���[�N���X�̃|�C���^

	std::unique_ptr<DoTween> dotween;

	DIRECTION direction;

	bool canMoveDir[4];	// �ړ��\�ł������

	bool isMoving;	// �ړ��\�t���O

	bool isMovingTrigger;	// isMove = true->false�ɕς�����u�Ԃ���true

	float moveTime = 0.0f;	// ��

public:
	PlayerMove(Player* _p);

	void Update();
	void Move(Vector3 _nowpos ,Vector3 _targetpos);

	// �ړ��I�����u�ԂɎ��̈ړ��̂��߂̏���������֐�
	void SettingMove();

	~PlayerMove();

	bool GetIsMoving()const { return isMoving; }
	DIRECTION GetDirection()const { return direction; }
};

