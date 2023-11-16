#pragma once
#include "CObject.h"
class DoTween;

class CFade :
    public CObject
{
public:
    enum FadeType
    {
        DEFAULT,
        LEFT,
        RIGHT,
        UP,
        DOWN,
    };
    enum FadeState
    {
        NO_FADE,
        FADE_IN,
        FADE_OUT
    };
private:
    FadeType fadeType;
    FadeState fadeState = FadeState::NO_FADE;

    DoTween *doTween;
public:
    CFade(D3DBUFFER vb, D3DTEXTURE tex);
    ~CFade();

    void FadeIn(FadeType _fadeType);
    void FadeOut();
    void FadeOut(FadeType _fadeType);

    void Draw();
    void Update();
};

