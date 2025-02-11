#pragma once
#include "PlayerMove.h"

class FatMove :
    public PlayerMove
{
public:
    FatMove(Player* _p);

    void Move(DIRECTION _dir) override;

    // どの方向に移動ができるか取得する関数
    void CheckCanMove()override;

    ~FatMove();
};

