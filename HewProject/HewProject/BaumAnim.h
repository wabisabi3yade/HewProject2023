#pragma once
#include "CAnimation.h"
class BaumAnim :
    public CAnimation
{

    enum class PATTERN
    {
        DEFAULT,
        BAUM,
    };
    float animRate;
    bool AnimEnd;
public:
    BaumAnim();
    ~BaumAnim();
    void Update()override;

    void PlayAnim(int _dir, float _animRate = 1.0f);

    bool GetAnimEnd()const { return AnimEnd; }
};

