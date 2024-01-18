#include "COperation.h"
#include  <iostream>

#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  30000

//コメント

GameController::GameController()
{
}

GameController::~GameController()
{
}

void GameController::GamePad()
{
	// XInputからコントローラの状態を取得
	if (XInputGetState(0, &controllerState) == ERROR_SUCCESS)
	{
		// スティックの値の取得
		stick_L.x = static_cast<float>(controllerState.Gamepad.sThumbLX) / 32767.0f;
		stick_L.y= static_cast<float>(controllerState.Gamepad.sThumbLY) / 32767.0f;

		if (abs(stick_L.x) < deadZone_L.x)
		{
			stick_L.x = 0.0f;
		}

		if (abs(stick_L.y) < deadZone_L.y)
		{
			stick_L.y = 0.0f;
		}

		//// デッドゾーン以内の入力なら
		//if (abs(stick_L.x) < 0.95 && abs(stick_L.y) < 0.95)
		//{
		//	// スティックの傾き0にするs
		//	stick_L = {};
		//}
	}

	return;
}

//Vector3 GameController::GamePad(float stickX, float stickY)
//{
//
//
//		// XInputからコントローラの状態を取得
//	if (XInputGetState(0, &controllerState) == ERROR_SUCCESS)
//	{
//		// スティックの値の取得
//		stickX = static_cast<float>(controllerState.Gamepad.sThumbLX) / 32767.0f;
//		stickY = static_cast<float>(controllerState.Gamepad.sThumbLY) / 32767.0f;
//
//		if (abs(stickX) < 0.95 && abs(stickY) < 0.95) return Vector3::zero;
//
//		return (stickX, stickY, 0);
//	}
//
//		/*if (XInputGetState(0, &m_controllerState) == ERROR_SUCCESS)
//		{
//			if (m_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
//			{
//				d.y = -1;// 下方向ベクトル
//				moveSpeed = 0.01f;
//			}
//		}*/
//
//}