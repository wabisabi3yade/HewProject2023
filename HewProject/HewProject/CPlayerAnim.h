#pragma once
#include "CAnimation.h"
class CPlayerAnim :
    public CAnimation
{
public:
    enum class PATTERN
    {
        STAY_DOWN,	// 待機下
        STAY_LEFT,	// 待機左
        STAY_RIGHT,	// 待機右
        STAY_UP,	// 待機上

        WALK_DOWN,	// 歩き下
        WALK_LEFT,	// 歩き左
        WALK_RIGHT,	// 歩き右
        WALK_UP,    // 歩き左
    };
private:
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

