#pragma once
#include "PlayerMove.h"

class FatMove :
    public PlayerMove
{
public:
    FatMove(Player* _p);

    void Move(DIRECTION _dir) override;

    void Step() override;

    // ‚Ç‚Ì•ûŒü‚ÉˆÚ“®‚ª‚Å‚«‚é‚©æ“¾‚·‚éŠÖ”
    void CheckCanMove()override;

    ~FatMove();
};

