#pragma once
#include "PlayerMove.h"

#define CASTELLAWALK_TIME (1.5f)    // ƒJƒXƒeƒ‰‚ÅˆÚ“®‚·‚éŠÔ

// ƒKƒŠó‘Ô‚Ì“®‚«
class ThinMove :
    public PlayerMove
{
public:
    ThinMove(Player* _p);

    void Move(DIRECTION _dir) override;

    // ‚Ç‚Ì•ûŒü‚ÉˆÚ“®‚ª‚Å‚«‚é‚©æ“¾‚·‚éŠÖ”
    void CheckCanMove()override;

    ~ThinMove();
};

