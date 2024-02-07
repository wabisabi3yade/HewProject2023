#pragma once
#include "CAnimation.h"
class CannonAnim :
    public CAnimation
{
    enum class PATTERN
    {
        IDLE,
        TURN,
        L_DIR = 3,//¶•ûŒü
        R_DIR,//‰E•ûŒü
        D_DIR,//‰º•ûŒü
        U_DIR,//ã•ûŒü
    };

    float AnimSpeedRate;


public:
    CannonAnim();
    ~CannonAnim();

    void Update() override;
    void PlayTurn(int _dir, float _animSpeedRate = 1.0f);
    void PlayStart(int _dir, float _animSpeedRate = 1.0f);

};

