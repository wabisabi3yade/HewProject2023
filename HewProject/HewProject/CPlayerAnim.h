#pragma once
#include "CAnimation.h"
class CPlayerAnim :
    public CAnimation
{
    float AnimSpeedRate;
    bool Now_IsFall;
    bool Old_IsFall;
public:
    CPlayerAnim();
    ~CPlayerAnim();
    void Update()override;
    void PlayWalk(int num , float _animSpeedRate = 1);
    void StopWalk();
    void PlayFall(int _num, float _animSpeedRate = 1);
    bool GetIsFall() { return Now_IsFall; }
    bool GetOldIsFall() { return Old_IsFall; }
    void SetIsFall(bool _isFall) { Now_IsFall = _isFall ;}
};

