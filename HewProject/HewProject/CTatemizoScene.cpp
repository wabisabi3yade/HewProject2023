#include "CTatemizoScene.h"
#include "CSceneManager.h"


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

    // �L�[����ňړ�
    // �L�[�����݉�����Ă邩�𔻒肷��@���@�L�[�v���X
    if (gInput->GetKeyPress(VK_DOWN))
    {
        charObj->SetDir(Vector3::down);
        d.y = -1;// �������x�N�g��
        moveSpeed = 0.01f;
    }
    if (gInput->GetKeyPress(VK_LEFT))
    {
        charObj->SetDir(Vector3::left);
        d.x = -1;// �������x�N�g��
        moveSpeed = 0.01f;
    }
    if (gInput->GetKeyPress(VK_RIGHT))
    {
        charObj->SetDir(Vector3::right);
        d.x = 1;//�E�����x�N�g��
        moveSpeed = 0.01f;
    }
    if (gInput->GetKeyPress(VK_UP))
    {
        charObj->SetDir(Vector3::up);
        d.y = 1;// ������x�N�g��
        moveSpeed = 0.01f;
    }

    // �L�[����Ńx�N�g�����ݒ肳��Ă�����dir�ɑ������
    if (d.x != 0.0f || d.y != 0.0f)
    {
        dir = d;
    }

    //DirectX::XMVECTOR v = XMLoadFloat3(dirChange(this->dir));
    //v = DirectX::XMVector3Normalize(v);
    //XMStoreFloat3(dirChange(this->dir), v);

    // �x�N�g�����g���Ĉړ�
    charObj->SetMoveSpeed(moveSpeed);
    pos.x = pos.x + dir.x * moveSpeed;
    pos.y = pos.y + dir.y * moveSpeed;
    pos.z = pos.z + dir.z * moveSpeed;

    charObj->Update();
}

void CTatemizoScene::LateUpdate()
{
}

void CTatemizoScene::Draw()
{
	charObj->Draw();
}
