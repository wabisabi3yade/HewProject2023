#pragma once
#include "CObject.h"

class CStageSelectPlayer :
    public CObject
{
public:

    // ����
    enum class DIRECTION
    {
        DOWN,
        LEFT,
        RIGHT,
        UP,
        NUM
    };

    bool isMoving;       //�ړ��ł��邩�ǂ���
    bool isChangeScene;  //�V�[���ϊ��t���O
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

    //�t���O������
    void FlagInit();
};

