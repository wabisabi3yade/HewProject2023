#pragma once
#include "CAnimation.h"
class CEffectAnim :
    public CAnimation
{
public:
    enum EffectPattertn
    {
        FX_0_11,
    };

public:
    CEffectAnim();

    void Update() override;

    ~CEffectAnim();
};

