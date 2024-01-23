#pragma once
#include "UI.h"
class NowLoadingText :
    public UI
{
    enum class TEXT
    {
        N,
        o_1,    // o 1‚Â–Ú
        w,
        L,
        o_2,    // o 2‚Â–Ú 
        a,
        d,
        i,
        n,
        g,
        period,
        NUM // ”
    };

    // •¶š‚ÌUI
    UI* text[static_cast<int>(TEXT::NUM)];
    // •¶š“®‚©‚·‚Æ‚«‚ÌŠp“x
    float degree[static_cast<int>(TEXT::NUM)];


    UI* character;

    D3DBUFFER buffer;

public:
    NowLoadingText();
    ~NowLoadingText();

    void Update() override;
    void Draw() override;

    // ‘S‘Ì‚ÉZÀ•W‚ğİ’è‚·‚é
    void SetPosZ(float _setZ);
};

