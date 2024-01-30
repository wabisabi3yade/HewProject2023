#pragma once
#include "UI.h"

#define MARKNUM_MAX (15)    // カロリーゲージの目盛の最大数

// カロリーゲージの15個の目盛りを操るクラス
class CalorieMark
{
    // 目盛り
    UI* mark[MARKNUM_MAX];
    D3DTEXTURE markTex;
    D3DBUFFER markBuffer;

    const float baseRadius = 1.6f;   // ゲージの目盛りの半径 
    Transform mTransform;   // 目盛り全体のトランスフォーム

public:
    CalorieMark();
    ~CalorieMark();

    void Update();
    void Draw();

    void SetPosition(const Vector3& _setPos);
    void SetScale(const Vector3& _setScale);
};

