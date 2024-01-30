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

        PANIC_DOWN, //焦っている歩き下
        PANIC_LEFT, //焦っている歩き左
        PANIC_RIGHT,//焦っている歩き右
        PANIC_UP,   //焦っている歩き上

        CANNON_DOWN, //大砲の動き下
        CANNON_LEFT, //大砲の動き左
        CANNON_RIGHT,//大砲の動き右
        CANNON_UP,   //大砲の動き上
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
    void StopWalk(int _num = 0);
    void PlayFall(int _num, float _animSpeedRate = 1);
    void PlayCannon(int _dir, float _animSpeedRate = 1);
    bool GetIsFall() { return Now_IsFall; }
    bool GetOldIsFall() { return Old_IsFall; }
    void SetIsFall(bool _isFall) { Now_IsFall = _isFall ;}
    void SetAnimSpeedRate(float _animSpeedRate) { AnimSpeedRate = _animSpeedRate; }
};

