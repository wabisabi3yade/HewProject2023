#pragma once
#include "PlayerMove.h"

class NormalMove :
	public PlayerMove
{
public:
	NormalMove(Player* _p);

	// �ړ��֐�
	void Move(DIRECTION _dir) override;

	void Step() override;

	// �ǂ̕����Ɉړ����ł��邩�擾����֐�
	void  CheckCanMove() override;

	~NormalMove();
};
