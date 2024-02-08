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
        L_DIR,//左方向
        R_DIR,//右方向
        D_DIR,//下方向
        U_DIR,//上方向

        //戻るアニメーション
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

