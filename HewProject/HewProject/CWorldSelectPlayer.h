#pragma once
#include "CGridObject.h"
#include "DoTween.h"
#include <iostream>

class CWorldSelectPlayer :
    public CGridObject
{
public:
    // ����
    enum class DIRECTION
    {
        DOWN,	// ��
        LEFT,	// ��
        RIGHT,	// �E
        UP,	// ��
        NUM,
        EVERY,	// �S���ʈړ��\�i�L�����̉摜�̌����͉������j
    };
    
    
    std::unique_ptr<DoTween> dotween;

    bool isNoPush;       //�ړ����ɉ��������Ȃ�
    bool isMoving;       //�ړ��ł��邩�ǂ���
    bool isChangeScene;  //�V�[���ϊ��t���O

    int nNumSelectScene;


    CWorldSelectPlayer(D3DBUFFER vb, D3DTEXTURE tex);
    ~CWorldSelectPlayer();
    void Update();
    void Draw();

};

