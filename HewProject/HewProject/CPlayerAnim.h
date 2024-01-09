#pragma once
#include "CAnimation.h"
class CPlayerAnim :
    public CAnimation
{
public:
    CPlayerAnim();
    ~CPlayerAnim();
    void Update()override;
    void PlayWalk(int num);
    void StopWalk();
};

