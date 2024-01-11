#include "COperation.h"
#include  <iostream>


GameController::GameController()
{
}

GameController::~GameController()
{
}

void GameController::Update()
{
	if (isPlayer)
	{
		// 操作で設定する用のベクトル変数
		Vector3 d = { 0.0f,0.0f,0.0f };

		// 移動速度を初めに０にする
		moveSpeed = 0.0f;

		dir = { 0,0,0 };

		if (XInputGetState(0, &m_controllerState) == ERROR_SUCCESS)
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
				d.x = 1;//右方向ベクトル
				moveSpeed = 0.01f;
			}
			if (m_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
			{
				d.y = 1;// 上方向ベクトル
				moveSpeed = 0.01f;
			}
		}
		// キー操作でベクトルが設定されていたらdirに代入する
		if (d.x != 0.0f || d.y != 0.0f)
		{
			dir = d;
		}
	}
	// ベクトルを使って移動
	pos.x = pos.x + dir.x * moveSpeed;
	pos.y = pos.y + dir.y * moveSpeed;
	pos.z = pos.z + dir.z * moveSpeed;
}