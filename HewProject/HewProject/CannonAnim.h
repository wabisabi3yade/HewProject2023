#pragma once
#include "CAnimation.h"
class CannonAnim :
    public CAnimation
{
    enum class PATTERN
    {
        IDLE,
        TURN,
        L_DIR = 3,//������
        R_DIR,//�E����
        D_DIR,//������
        U_DIR,//�����
    };

    float AnimSpeedRate;


public:
    CannonAnim();
    ~CannonAnim();

    void Update() override;
    void PlayTurn(int _dir, float _animSpeedRate = 1.0f);
    void PlayStart(int _dir, float _animSpeedRate = 1.0f);

};

