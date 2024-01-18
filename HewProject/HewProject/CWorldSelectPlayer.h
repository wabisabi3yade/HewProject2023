#pragma once
#include "CGridObject.h"
#include "DoTween.h"
#include <iostream>

class CWorldSelectPlayer :
    public CGridObject
{
public:
    std::unique_ptr<DoTween> dotween;

    bool isNoPush;       //�ړ����ɉ��������Ȃ�
    bool isMoving;       //�ړ��ł��邩�ǂ���
    bool isChangeScene;  //�V�[���ϊ��t���O

    int nNumSelectScene;

    CWorldSelectPlayer(D3DBUFFER vb, D3DTEXTURE tex);
    ~CWorldSelectPlayer();
    void Update();
    void Draw();

    //�t���O������
    void FlagInit();
};

