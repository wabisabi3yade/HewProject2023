#pragma once
#include "PlayerMove.h"
class MuscleMove :
    public PlayerMove
{
public:
    MuscleMove(Player* _p);
    ~MuscleMove();

    void Move(DIRECTION _dir) override;

    void CheckCanMove()override;
};

