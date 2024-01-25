#include <DirectXMath.h>
#include "CTatemizoScene.h"
#include "CInput.h"
#include "COperation.h"
#include <iostream>


CTatemizoScene::CTatemizoScene()
{
	D3D_CreateSquare({ 3,4 }, &charBuffer);
	D3D_LoadTexture(L"asset/hashimoto/Char01.png", &charTexture);

	charObj = new CObject(charBuffer, charTexture);
	charObj->mTransform.scale = { 3.0f,3.0f,1.0f };

	val = new GameController();
	button = new GameController();

}

CTatemizoScene::~CTatemizoScene()
{
	CLASS_DELETE(charObj);

	SAFE_RELEASE(charBuffer);

	SAFE_RELEASE(charTexture);

	CLASS_DELETE(val);

	CLASS_DELETE(button);
}

void CTatemizoScene::Update()
{
	/**************************************** 
	   �X�e�B�b�N�̑���
	   L�X�e�B�b�N�̓f�b�h�]�[������
	   R�X�e�B�b�N�̓f�b�h�]�[������
	*****************************************/
		dir = { 0,0 };

		//�X�e�B�b�N�̊֐��Ăяo��
		val->PadStick();

		ButtonState();

		Vector2 L = val->GetStick_L();
		Vector2 R = val->GetStick_R();
		
		// ���X�e�B�b�N�̑���n��
		if (val->GetStick_L().x > 0)
		{
			// �E��
			if (val->GetStick_L().y > 0)
			{
				dir = { 1,1 };
			}
			// �E��
			if (val->GetStick_L().y < 0)
			{
				dir = { 1,-1 };
			}
		}

		if (val->GetStick_L().x < 0)
		{
			// ����			
			if (val->GetStick_L().y > 0)
			{
				dir = { -1,1 };
			}
			// ����
			if (val->GetStick_L().y < 0)
			{
				dir = { -1,-1 };
			}
		}
		/*���X�e�B�b�N�����܂�*/

		// �E�X�e�B�b�N�̑���n��
		if (val->GetStick_R().x > 0)
		{
			if (val->GetStick_R().y > 0)
			{
				dir = { 1,1 };
			}
			if (val->GetStick_R().y < 0)
			{
				dir = { 1,-1 };
			}
		}

		if (val->GetStick_R().x < 0)
		{
			if (val->GetStick_R().y > 0)
			{
				dir = { -1,1 };
			}
			if (val->GetStick_R().y < 0)
			{
				dir = { -1,-1 };
			}
		}
		/*�E�X�e�B�b�N�����܂�*/


		//�|�W�V����(���W)�̕ύX�ŃL�����̈ړ�
		charObj->mTransform.pos.x += dir.x * 0.1;
		charObj->mTransform.pos.y += dir.y * 0.1;

}

void CTatemizoScene::LateUpdate()
{
}

void CTatemizoScene::Draw()
{
	charObj->Draw();
}

void CTatemizoScene::ButtonState()
{
	// �{�^��A�������ꂽ�ꍇ
	if (button->Button(XINPUT_GAMEPAD_A))
	{
		// �����ɉ��炩�̏���������
	}

	// �{�^��B�������ꂽ�ꍇ
	if (button->Button(XINPUT_GAMEPAD_B))
	{
		// �����ɉ��炩�̏���������
	}

	// �{�^��X�������ꂽ�ꍇ
	if (button->Button(XINPUT_GAMEPAD_X))
	{
		// �����ɉ��炩�̏���������
	}

	// �{�^��Y�������ꂽ�ꍇ
	if (button->Button(XINPUT_GAMEPAD_Y))
	{
		// �����ɉ��炩�̏���������
	}
}
