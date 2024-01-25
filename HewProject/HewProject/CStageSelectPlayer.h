#pragma once
#include "CObject.h"

class CStageSelectPlayer :
    public CObject
{
public:

    // 方向
    enum class DIRECTION
    {
        DOWN,
        LEFT,
        RIGHT,
        UP,
        NUM
    };

    bool isMoving;       //移動できるかどうか
    bool isChangeScene;  //シーン変換フラグ
    bool isOnAnim_Left;
    bool isOnAnim_Right;
    bool isOnAnim_Up;
    bool isOnAnim_Down;
    bool isDiagonal;

    int nNumSelectScene;

    DIRECTION playerDir;

    CStageSelectPlayer(D3DBUFFER vb, D3DTEXTURE tex);
    ~CStageSelectPlayer();
    void Update();
    void Draw();

    //フラグ初期化
    void FlagInit();
};

