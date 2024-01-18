#pragma once
#include "CGridObject.h"
#include "DoTween.h"
#include <iostream>

class CWorldSelectPlayer :
    public CGridObject
{
public:
    std::unique_ptr<DoTween> dotween;

    bool isNoPush;       //移動中に何も押せない
    bool isMoving;       //移動できるかどうか
    bool isChangeScene;  //シーン変換フラグ

    int nNumSelectScene;

    CWorldSelectPlayer(D3DBUFFER vb, D3DTEXTURE tex);
    ~CWorldSelectPlayer();
    void Update();
    void Draw();

    //フラグ初期化
    void FlagInit();
};

