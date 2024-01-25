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
	   スティックの操作
	   Lスティックはデッドゾーンあり
	   Rスティックはデッドゾーン無し
	*****************************************/
		dir = { 0,0 };

		//スティックの関数呼び出し
		val->PadStick();

		ButtonState();

		Vector2 L = val->GetStick_L();
		Vector2 R = val->GetStick_R();
		
		// 左スティックの操作系統
		if (val->GetStick_L().x > 0)
		{
			// 右上
			if (val->GetStick_L().y > 0)
			{
				dir = { 1,1 };
			}
			// 右下
			if (val->GetStick_L().y < 0)
			{
				dir = { 1,-1 };
			}
		}

		if (val->GetStick_L().x < 0)
		{
			// 左上			
			if (val->GetStick_L().y > 0)
			{
				dir = { -1,1 };
			}
			// 左下
			if (val->GetStick_L().y < 0)
			{
				dir = { -1,-1 };
			}
		}
		/*左スティックここまで*/

		// 右スティックの操作系統
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
		/*右スティックここまで*/


		//ポジション(座標)の変更でキャラの移動
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
	// ボタンAが押された場合
	if (button->Button(XINPUT_GAMEPAD_A))
	{
		// ここに何らかの処理を書く
	}

	// ボタンBが押された場合
	if (button->Button(XINPUT_GAMEPAD_B))
	{
		// ここに何らかの処理を書く
	}

	// ボタンXが押された場合
	if (button->Button(XINPUT_GAMEPAD_X))
	{
		// ここに何らかの処理を書く
	}

	// ボタンYが押された場合
	if (button->Button(XINPUT_GAMEPAD_Y))
	{
		// ここに何らかの処理を書く
	}
}
