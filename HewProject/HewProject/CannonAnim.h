#pragma once
#include "CAnimation.h"
class CannonAnim :
    public CAnimation
{
    enum class PATTERN
    {
        IDLE,
        LR_TURN,
        UD_TURN,
        L_DIR,//������
        R_DIR,//�E����
        D_DIR,//������
        U_DIR,//�����

        //�߂�A�j���[�V����
        L_RETURN,
        R_RETURN,
        D_RETURN,
        U_RETURN,
    };

    float AnimSpeedRate;

    int dir;
public:
    CannonAnim();
    ~CannonAnim();

    void Update() override;
    void PlayTurn(int _dir, float _animSpeedRate = 1.0f);
    void PlayStart(int _dir, float _animSpeedRate = 1.0f);
    void PlayReturn(float _animSpeedRate = 1.0f);
};

