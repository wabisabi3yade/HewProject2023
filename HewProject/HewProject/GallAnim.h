#pragma once
#include "CAnimation.h"
class GallAnim :
    public CAnimation
{
    enum class PATTERN
    {
        IDLE,
        OPEN,
    };

    float AnimSpeedRate;

public:
    GallAnim();
    ~GallAnim();
    void Update() override;

    void PlayOpen(float _animSpeedRate);
};

