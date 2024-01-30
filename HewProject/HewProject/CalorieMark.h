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

    const float baseRadius = 1.6f;   // �Q�[�W�̖ڐ���̔��a 
    Transform mTransform;   // �ڐ���S�̂̃g�����X�t�H�[��

public:
    CalorieMark();
    ~CalorieMark();

    void Update();
    void Draw();

    void SetPosition(const Vector3& _setPos);
    void SetScale(const Vector3& _setScale);
};

