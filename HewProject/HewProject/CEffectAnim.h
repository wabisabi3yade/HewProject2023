#pragma once
#include "CAnimation.h"
class CEffectAnim :
    public CAnimation
{
    bool AnimEnd;
public:
    enum EffectPattertn
    {
        FX_0_11,
    };

public:
    CEffectAnim();
    ~CEffectAnim();

    void Update() override;

    bool isCheck = false;

    void SetEffectLoop(bool);

    bool GetAnimEnd()const { return AnimEnd; }

};

