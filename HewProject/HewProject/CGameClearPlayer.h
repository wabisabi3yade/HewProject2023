#pragma once
#include "CObject.h"

class CGameClearPlayer :
    public CObject
{
public:
    // 方向
    enum class DIRECTION
    {
        DOWN,	// 下
        LEFT,	// 左
        RIGHT,	// 右
        UP,	// 上
        NUM,
        EVERY,	// 全方位移動可能（キャラの画像の向きは下向き）
    };

    bool isEatAnim;
    bool isWalkAnim;
public:
    CGameClearPlayer(D3DBUFFER vb, D3DTEXTURE tex);
    ~CGameClearPlayer();
    void Update() override;
    void Draw() override;
};

