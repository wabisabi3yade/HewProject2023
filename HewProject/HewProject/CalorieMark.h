#pragma once
#include "UI.h"

#define MARKNUM_MAX (15)    // �J�����[�Q�[�W�̖ڐ��̍ő吔

// �J�����[�Q�[�W��15�̖ڐ���𑀂�N���X
class CalorieMark
{
    // �ڐ���
    UI* mark[MARKNUM_MAX];
    D3DTEXTURE markTex;
    D3DBUFFER markBuffer;

    float radius;   // �Q�[�W�̖ڐ���̔��a
    Transform mTransform;   // �ڐ���S�̂̃g�����X�t�H�[��

public:
    CalorieMark();
    ~CalorieMark();

    void Update();
    void Draw();
};

