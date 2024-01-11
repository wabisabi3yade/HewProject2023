#include <DirectXMath.h>
#include "direct3d.h"
#include "CTatemizoScene.h"
#include "CInput.h"

extern CInput* gInput;

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
	if (isPlayer)
	{
		// ����Őݒ肷��p�̃x�N�g���ϐ�
		Vector3 d = { 0.0f,0.0f,0.0f};

		/*// �����Ȃ��x�N�g���ɐݒ�
		d.x = 0;
		d.y = 0;
		d.z = 0;*/

		// �ړ����x�����߂ɂO�ɂ���
		moveSpeed = 0.0f;

		//dir = { 0,0,0 };

		//���쎎��
		if (gInput->GetKeyPress(VK_DOWN))
		{
			d.y = -1;// �������x�N�g��
			moveSpeed = 0.01f;
		}
		if (gInput->GetKeyPress(VK_LEFT))
		{
			d.x = -1;// �������x�N�g��
			moveSpeed = 0.01f;
		}
		if (gInput->GetKeyPress(VK_RIGHT))
		{
			d.x = 1;//�E�����x�N�g��
			moveSpeed = 0.01f;
		}
		if (gInput->GetKeyPress(VK_UP))
		{
			d.y = 1;// ������x�N�g��
			moveSpeed = 0.01f;
		}
		//if (XInputGetState(0, &m_controllerState) == ERROR_SUCCESS)
		//{
		//	if (m_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		//	{
		//		dir.y = 1;
		//		d.y = -1;// �������x�N�g��
		//		moveSpeed = 0.01f;
		//	}
		//}

		// �L�[����Ńx�N�g�����ݒ肳��Ă�����dir�ɑ������
		if (d.x != 0.0f || d.y != 0.0f)
		{
			dir = d;
		}

		charObj->SetDir(dir);

		charObj->Update();
	}

	// �x�N�g�����g���Ĉړ�
	pos.x = pos.x + dir.x * moveSpeed;
	pos.y = pos.y + dir.y * moveSpeed;
	pos.z = pos.z + dir.z * moveSpeed;

}

void CTatemizoScene::LateUpdate()
{
}

void CTatemizoScene::Draw()
{
	charObj->Draw();
}
