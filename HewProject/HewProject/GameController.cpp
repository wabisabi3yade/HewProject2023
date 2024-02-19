#include "GameController.h"
#include  <iostream>

#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  30000

// インスタンスを初期化
GameController* GameController::instance = nullptr;

// コメントであそぼ

GameController::GameController()
{
	ZeroMemory(&ControllerState, sizeof(XINPUT_STATE));
}

GameController::~GameController()
{
}

GameController* GameController::GetInstance()
{
	// インスタンスを取得するs
	if (instance == nullptr)
	{
		instance = new GameController();
	}

	// インスタンスを返す
	return instance;
}

void GameController::Delete()
{
	// インスタンスを削除する
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void GameController::PadStick()
{
	// 最初に初期化する
	stick_L = Vector2::zero;

	// XInputからコントローラの状態を取得
	if (XInputGetState(0, &ControllerState) == ERROR_SUCCESS)
	{
		// Lスティックの値の取得
		stick_L.x = static_cast<float>(ControllerState.Gamepad.sThumbLX) / 32767.0f;
		stick_L.y = static_cast<float>(ControllerState.Gamepad.sThumbLY) / 32767.0f;

		//// Rスティックの値の取得
		//stick_R.x = static_cast<float>(ControllerState.Gamepad.sThumbRX) / 32767.0f;
		//stick_R.y = static_cast<float>(ControllerState.Gamepad.sThumbRY) / 32767.0f;

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


