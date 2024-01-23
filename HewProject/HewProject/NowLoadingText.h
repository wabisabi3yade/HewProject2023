#pragma once
#include "UI.h"
class NowLoadingText :
    public UI
{
    enum class TEXT
    {
        N,
        o_1,    // o 1つ目
        w,
        L,
        o_2,    // o 2つ目 
        a,
        d,
        i,
        n,
        g,
        period,
        NUM // 数
    };

    // 文字のUI
    UI* text[static_cast<int>(TEXT::NUM)];
    // 文字動かすときの角度
    float degree[static_cast<int>(TEXT::NUM)];


    UI* character;

    D3DBUFFER buffer;

public:
    NowLoadingText();
    ~NowLoadingText();

    void Update() override;
    void Draw() override;

    // 全体にZ座標を設定する
    void SetPosZ(float _setZ);
};

