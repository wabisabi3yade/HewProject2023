#pragma once
#include "CGridObject.h"
#include "DoTween.h"

class CTitlePlayer :
    public CGridObject
{
public:
    enum class DIRECTION
    {
        DOWN,	// 下
        LEFT,	// 左
        RIGHT,	// 右
        UP,	// 上
        NUM,
        EVERY,	// 全方位移動可能（キャラの画像の向きは下向き）
    };


    std::unique_ptr<DoTween> dotween;

    bool isNormal;
    bool isFat;
    bool isThin;
    bool isAll;
    bool isStopMove;

    int nRandomChara;
    int nAction;

public:
    CTitlePlayer(D3DBUFFER vb, D3DTEXTURE tex);
    ~CTitlePlayer();
    void Update();
    void Draw();
};

