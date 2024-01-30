#pragma once
#include "CGridObject.h"
#include "DoTween.h"
#include <iostream>

class CWorldSelectPlayer :
    public CGridObject
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
    
    
    std::unique_ptr<DoTween> dotween;

    bool isNoPush;       //移動中に何も押せない
    bool isMoving;       //移動できるかどうか
    bool isChangeScene;  //シーン変換フラグ

    int nNumSelectScene;


    CWorldSelectPlayer(D3DBUFFER vb, D3DTEXTURE tex);
    ~CWorldSelectPlayer();
    void Update();
    void Draw();

};

