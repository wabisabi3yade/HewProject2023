#pragma once
#include "PlayerMove.h"

class FatMove :
    public PlayerMove
{
public:
    FatMove(Player* _p);

    void Move(DIRECTION _dir) override;

    // �ǂ̕����Ɉړ����ł��邩�擾����֐�
    void CheckCanMove()override;

    ~FatMove();
};

