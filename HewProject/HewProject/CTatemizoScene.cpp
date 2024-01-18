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
		// 操作で設定する用のベクトル変数
		//V/*ector3 d = { 0.0f,0.0f,0.0f };*/

		dir = { 0,0,0 };

		x->GamePad();

		/*dir.x = x->GetStick_L().x;
		dir.y = x->GetStick_L().y;*/

		Vector2 a = x->GetStick_L();
		
		if (x->GetStick_L().x > 0)
		{
			// 右上
			if (x->GetStick_L().y > 0)
			{
				dir = { 1,1,0 };
			}

			// 右下
			if (x->GetStick_L().y < 0)
			{
				dir = { 1,-1,0 };
			}

		}

		if (x->GetStick_L().x < 0)
		{
			// 左上			
			if (x->GetStick_L().y > 0)
			{
				dir = { -1,1,0 };
			}

			// 左下
			if (x->GetStick_L().y < 0)
			{
				dir = { -1,-1,0 };
			}

		}
	


		/*Vector3 G(x->GamePad(0.0, 0.0));*/


			/*//右上
			if ((stickX <= 1) && (stickX > 0.5) && (stickY >= 0.25))
			{
				d.y = 1;// 上方向ベクトル
				moveSpeed = 0.01f;

				d.x = 1;// 右方向ベクトル
				moveSpeed = 0.01f;
			}
			//右下
			if ((stickX <= 1) && (stickX > 0.25) && (stickY < -0.25))
			{
				d.y = -1;// 上方向ベクトル
				moveSpeed = 0.01f;

				d.x = 1;// 右方向ベクトル
				moveSpeed = 0.01f;
			}
			//左下
			if ((stickX < 0) && (stickY < 0))
			{
				d.y = -1;// 上方向ベクトル
				moveSpeed = 0.01f;

				d.x = -1;// 右方向ベクトル
				moveSpeed = 0.01f;
			}
			//左上
			if ((stickX < 0) && (stickY > 0.25))
			{
				d.y = 1;// 上方向ベクトル
				moveSpeed = 0.01f;

				d.x = -1;// 右方向ベクトル
				moveSpeed = 0.01f;
			}*/

			// キー操作でベクトルが設定されていたらdirに代入する
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
