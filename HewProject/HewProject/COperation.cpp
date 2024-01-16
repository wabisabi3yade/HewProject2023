#include "COperation.h"
#include  <iostream>


GameController::GameController()
{
}

GameController::~GameController()
{
}

Vector3 GameController::GamePad()
{
	if (isPlayer)
	{
		// 操作で設定する用のベクトル変数
		Vector3 d = { 0.0f,0.0f,0.0f };

		// 移動速度を初めに０にする
		moveSpeed = 0.0f;

		dir = { 0,0,0 };

		// XInputからコントローラの状態を取得
		if (XInputGetState(0, &controllerState) == ERROR_SUCCESS)
		{
			// スティックの値の取得
			float stickX = static_cast<float>(controllerState.Gamepad.sThumbLX) / 32767.0f;
			float stickY = static_cast<float>(controllerState.Gamepad.sThumbLY) / 32767.0f;

			// 移動度の設定
			float sensitivity = 2.0f;
			float moveX = stickX * sensitivity;
			float moveY = stickY * sensitivity;

			//右上
  			if ((moveX <= 2) && (moveX > 1) && (moveY >= 1))
			{
				d.y = 1;// 上方向ベクトル
				moveSpeed = 0.01f;

				d.x = 1;// 右方向ベクトル
				moveSpeed = 0.01f;
			}
			//右下
			if ((moveX >= 1) && (moveY > -2) && (moveY < -1))
			{
				d.y = -1;// 上方向ベクトル
				moveSpeed = 0.01f;

				d.x = 1;// 右方向ベクトル
				moveSpeed = 0.01f;
			}
			//左下
			if ((moveX < 0) && (moveY < 0))
			{
				d.y = -1;// 上方向ベクトル
				moveSpeed = 0.01f;

				d.x = -1;// 右方向ベクトル
				moveSpeed = 0.01f;
			}
			//左上
			if ((moveX < 0) && (moveY > 1))
			{
				d.y = 1;// 上方向ベクトル
				moveSpeed = 0.01f;

				d.x = -1;// 右方向ベクトル
				moveSpeed = 0.01f;
			}
		
		}

		/*if (XInputGetState(0, &m_controllerState) == ERROR_SUCCESS)
		{
			if (m_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
			{
				d.y = -1;// 下方向ベクトル
				moveSpeed = 0.01f;
			}
			if (m_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_X)
			{
				d.x = -1;// 左方向ベクトル
				moveSpeed = 0.01f;
			}
			if (m_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
			{
				d.x = 1;// 右方向ベクトル
				moveSpeed = 0.01f;
			}
			if (m_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
			{
				d.y = 1;// 上方向ベクトル
				moveSpeed = 0.01f;
			}
		}*/

		// キー操作でベクトルが設定されていたらdirに代入する
		if (d.x != 0.0f || d.y != 0.0f)
		{
			dir = d;
		}

		return d;
	}
	// ベクトルを使って移動
	pos.x = pos.x + dir.x * moveSpeed;
	pos.y = pos.y + dir.y * moveSpeed;
	pos.z = pos.z + dir.z * moveSpeed;

	
}