#pragma once
#include "PlayerMove.h"

#define CASTELLAWALK_TIME (1.5f)    // カステラで移動する時間

// ガリ状態の動き
class ThinMove :
    public PlayerMove
{
public:
    ThinMove(Player* _p);

    void Move(DIRECTION _dir) override;

    // どの方向に移動ができるか取得する関数
    void CheckCanMove()override;

    ~ThinMove();
};

