#pragma once
#include <iostream>

class Player;
class DoTween;

class PlayerMove
{
	std::unique_ptr<Player> player;	// �v���C���[�N���X�̃|�C���^

	std::unique_ptr<DoTween> dotween;

	bool isMoving;	// �ړ��\�t���O

public:
	PlayerMove(Player* _p);

	void Update();
	void Move();

	~PlayerMove();
};

