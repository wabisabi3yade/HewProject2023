#include <DirectXMath.h>
#include "direct3d.h"
#include "CTatemizoScene.h"
#include "CInput.h"
#include "COperation.h"


CTatemizoScene::CTatemizoScene()
{
	D3D_CreateSquare({ 3,4 }, &charBuffer);
	D3D_LoadTexture(L"asset/hashimoto/Char01.png", &charTexture);

	charObj = new CObject(charBuffer, charTexture);
	charObj->mTransform.scale = { 3.0f,3.0f,1.0f };

	x = new GameController();

}

CTatemizoScene::~CTatemizoScene()
{
	CLASS_DELETE(charObj);

	SAFE_RELEASE(charBuffer);

	SAFE_RELEASE(charTexture);

	CLASS_DELETE(x)
}

void CTatemizoScene::Update()
{


	if (isPlayer)
	{
		// ����Őݒ肷��p�̃x�N�g���ϐ�
		//V/*ector3 d = { 0.0f,0.0f,0.0f };*/

		dir = { 0,0,0 };

		x->GamePad();

		/*dir.x = x->GetStick_L().x;
		dir.y = x->GetStick_L().y;*/

		Vector2 a = x->GetStick_L();
		
		if (x->GetStick_L().x > 0)
		{
			// �E��
			if (x->GetStick_L().y > 0)
			{
				dir = { 1,1,0 };
			}

			// �E��
			if (x->GetStick_L().y < 0)
			{
				dir = { 1,-1,0 };
			}

		}

		if (x->GetStick_L().x < 0)
		{
			// ����			
			if (x->GetStick_L().y > 0)
			{
				dir = { -1,1,0 };
			}

			// ����
			if (x->GetStick_L().y < 0)
			{
				dir = { -1,-1,0 };
			}

		}
	


		/*Vector3 G(x->GamePad(0.0, 0.0));*/


			/*//�E��
			if ((stickX <= 1) && (stickX > 0.5) && (stickY >= 0.25))
			{
				d.y = 1;// ������x�N�g��
				moveSpeed = 0.01f;

				d.x = 1;// �E�����x�N�g��
				moveSpeed = 0.01f;
			}
			//�E��
			if ((stickX <= 1) && (stickX > 0.25) && (stickY < -0.25))
			{
				d.y = -1;// ������x�N�g��
				moveSpeed = 0.01f;

				d.x = 1;// �E�����x�N�g��
				moveSpeed = 0.01f;
			}
			//����
			if ((stickX < 0) && (stickY < 0))
			{
				d.y = -1;// ������x�N�g��
				moveSpeed = 0.01f;

				d.x = -1;// �E�����x�N�g��
				moveSpeed = 0.01f;
			}
			//����
			if ((stickX < 0) && (stickY > 0.25))
			{
				d.y = 1;// ������x�N�g��
				moveSpeed = 0.01f;

				d.x = -1;// �E�����x�N�g��
				moveSpeed = 0.01f;
			}*/

			// �L�[����Ńx�N�g�����ݒ肳��Ă�����dir�ɑ������
			/*if (d.x != 0.0f || d.y != 0.0f)
			{
				dir = d;
			}*/

			charObj->mTransform.pos.x += dir.x * 0.1;
			charObj->mTransform.pos.y += dir.y * 0.1;
	}

}

void CTatemizoScene::LateUpdate()
{
}

void CTatemizoScene::Draw()
{
	charObj->Draw();
}
