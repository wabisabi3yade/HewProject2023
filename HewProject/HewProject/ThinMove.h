#pragma once
#include "PlayerMove.h"

#define CASTELLAWALK_TIME (1.5f)    // �J�X�e���ňړ����鎞��

// �K����Ԃ̓���
class ThinMove :
    public PlayerMove
{
public:
    ThinMove(Player* _p);

    void Move(DIRECTION _dir) override;

    // �ǂ̕����Ɉړ����ł��邩�擾����֐�
    void CheckCanMove()override;

    ~ThinMove();
};

