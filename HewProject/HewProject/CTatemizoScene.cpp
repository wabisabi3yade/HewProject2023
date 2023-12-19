#include "CTatemizoScene.h"
#include "Ccontroller.h"

Input* gValue = new Input;

CTatemizoScene::CTatemizoScene()
{
	D3D_CreateSquare({ 3,4 }, &charBuffer);
	D3D_LoadTexture(L"asset/hashimoto/Char01.png", &charTexture);

	charObj = new CObject(charBuffer, charTexture);
	charObj->mTransform.scale = { 3.0f,3.0f,1.0f };
}

CTatemizoScene::~CTatemizoScene()
{
	CLASS_DELETE(charObj);

	SAFE_RELEASE(charBuffer);

	SAFE_RELEASE(charTexture);
}

void CTatemizoScene::Update()
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

    //�X�e�B�b�N�̒l�Ŋp�x�𔻒肵�ē�����
    CTatemizoScene::

	charObj->Update();
    // �x�N�g�����g���Ĉړ�
    //charObj->SetMoveSpeed(moveSpeed);
    //pos.x = pos.x + dir.x * moveSpeed;
    //pos.y = pos.y + dir.y * moveSpeed;
    //pos.z = pos.z + dir.z * moveSpeed;
}

void CTatemizoScene::LateUpdate()
{
}

void CTatemizoScene::Draw()
{
	charObj->Draw();
}
