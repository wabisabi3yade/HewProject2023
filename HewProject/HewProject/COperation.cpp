#include "COperation.h"

void COperation::Update()
{
    // ����Őݒ肷��p�̃x�N�g���ϐ�
    Vector3 d;

    // �����Ȃ��x�N�g���ɐݒ�
    d.x = 0;
    d.y = 0;
    d.z = 0;

    // �ړ����x�����߂ɂO�ɂ���
    moveSpeed = 0.0f;

    dir = { 0,0,0 };

    // �L�[����ňړ�
    // �L�[�����݉�����Ă邩�𔻒肷��@���@�L�[�v���X
    if (gInput->GetKeyPress(VK_DOWN))
    {
        dir.y = -1;
        d.y = -1;// �������x�N�g��
        moveSpeed = 0.01f;
    }
    if (gInput->GetKeyPress(VK_LEFT))
    {
        dir.x = -1;
        d.x = -1;// �������x�N�g��
        moveSpeed = 0.01f;
    }
    if (gInput->GetKeyPress(VK_RIGHT))
    {
        dir.x = +1;
        d.x = 1;//�E�����x�N�g��
        moveSpeed = 0.01f;
    }
    if (gInput->GetKeyPress(VK_UP))
    {
        dir.y = +1;
        d.y = 1;// ������x�N�g��
        moveSpeed = 0.01f;
    }

    charObj->SetDir(dir);

    charObj->Update();
}

void COperation::Draw()
{
}


