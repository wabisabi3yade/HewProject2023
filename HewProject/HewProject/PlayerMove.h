#pragma once
#include <iostream>

class Player;
class DoTween;

class PlayerMove
{
	std::unique_ptr<Player> player;	// �v���C���[�N���X�̃|�C���^

	std::unique_ptr<DoTween> dotween;

	//Vector3 target[4] = {};	// �ړI���W�i�㉺���E�j

	bool isMoving;	// �ړ��\�t���O

	float moveTime = 0.0f;	// ��

public:
	PlayerMove(Player* _p);

	void Update();
	void Move();

	~PlayerMove();
};

