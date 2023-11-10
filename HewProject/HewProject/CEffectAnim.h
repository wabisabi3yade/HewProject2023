#pragma once
#include "CAnimation.h"
class CEffectAnim :
    public CAnimation
{

public:
    CEffectAnim();

    void Update() override;

    ~CEffectAnim();
};

