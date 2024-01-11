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
		// 操作で設定する用のベクトル変数
		Vector3 d = { 0.0f,0.0f,0.0f};

		/*// 方向なしベクトルに設定
		d.x = 0;
		d.y = 0;
		d.z = 0;*/

		// 移動速度を初めに０にする
		moveSpeed = 0.0f;

		//dir = { 0,0,0 };

		//操作試し
		if (gInput->GetKeyPress(VK_DOWN))
		{
			d.y = -1;// 下方向ベクトル
			moveSpeed = 0.01f;
		}
		if (gInput->GetKeyPress(VK_LEFT))
		{
			d.x = -1;// 左方向ベクトル
			moveSpeed = 0.01f;
		}
		if (gInput->GetKeyPress(VK_RIGHT))
		{
			d.x = 1;//右方向ベクトル
			moveSpeed = 0.01f;
		}
		if (gInput->GetKeyPress(VK_UP))
		{
			d.y = 1;// 上方向ベクトル
			moveSpeed = 0.01f;
		}
		//if (XInputGetState(0, &m_controllerState) == ERROR_SUCCESS)
		//{
		//	if (m_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		//	{
		//		dir.y = 1;
		//		d.y = -1;// 下方向ベクトル
		//		moveSpeed = 0.01f;
		//	}
		//}

		// キー操作でベクトルが設定されていたらdirに代入する
		if (d.x != 0.0f || d.y != 0.0f)
		{
			dir = d;
		}

		charObj->SetDir(dir);

		charObj->Update();
	}

	// ベクトルを使って移動
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
