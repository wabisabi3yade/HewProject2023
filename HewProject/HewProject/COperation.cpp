#include "COperation.h"
#include  <iostream>

#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  30000

// コメントであそぼ

GameController::GameController()
{
}

GameController::~GameController()
{
}

void GameController::PadStick()
{
	// XInputからコントローラの状態を取得
	if (XInputGetState(0, &ControllerState) == ERROR_SUCCESS)
	{
		// Lスティックの値の取得
		stick_L.x = static_cast<float>(ControllerState.Gamepad.sThumbLX) / 32767.0f;
		stick_L.y = static_cast<float>(ControllerState.Gamepad.sThumbLY) / 32767.0f;

		// Rスティックの値の取得
		stick_R.x = static_cast<float>(ControllerState.Gamepad.sThumbRX) / 32767.0f;
		stick_R.y = static_cast<float>(ControllerState.Gamepad.sThumbRY) / 32767.0f;

		// X軸のデッドゾーン
		if (abs(stick_L.x) < deadZone_L.x)
		{
			stick_L.x = 0.0f;
		}

		// Y軸のデッドゾーン
		if (abs(stick_L.y) < deadZone_L.y)
		{
			stick_L.y = 0.0f;
		}
	}

	return;
}

bool GameController::Button(WORD button)
{
	if (XInputGetState(0, &ControllerState)== ERROR_SUCCESS)
	{
		return (ControllerState.Gamepad.wButtons & button) != 0;
	}
	return false;
}


