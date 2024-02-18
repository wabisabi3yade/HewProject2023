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

        EAT_RIGHT,   //食べる右向き
        EAT_LEFT,    //食べる左向き

        PUNCH,       //パンチ

        //バウムクーヘンの動き
        BAUM,

        //ゴール用のパンチ
        GALL_PUNCH,

        //ゴール用の食べるアニメーション
        GALL_EAT,

        //プレイヤーマッチョになるときのアニメーション
        MAKEOVER_RIGHT,
        MAKEOVER_LEFT,
    };
private:
    float AnimSpeedRate;
    bool Now_IsFall;
    bool Old_IsFall;
public:
    CPlayerAnim();
    ~CPlayerAnim();
    void Update()override;
    void PlayWalk(int num , float _animSpeedRate = 1.0f);
    void StopWalk(int _num = 0);
    void PlayFall(int _num, float _animSpeedRate = 1.0f);
    void PlayCannon(int _dir, float _animSpeedRate = 1.0f);
    void PlayEat(int _dir, float _animSpeedRate = 1.0f);
    void PlayPunch( float _animSpeedRate = 1.0f , bool _isGall = false);
    void PlayBaum(int _dir, float _animSpeedRate);
    bool GetIsFall() { return Now_IsFall; }
    bool GetOldIsFall() { return Old_IsFall; }
    void SetIsFall(bool _isFall) { Now_IsFall = _isFall ;}
    void SetAnimSpeedRate(float _animSpeedRate) { AnimSpeedRate = _animSpeedRate; }
    void PlayGallEat(float _animSpeedRate = 1.0f);
    void PlayMakeover(int _dir , float _animSpeedRate = 1.0f);
};

