#include "COperation.h"
#include  <iostream>

#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  30000

// �R�����g�ł�����

GameController::GameController()
{
}

GameController::~GameController()
{
}

void GameController::PadStick()
{
	// XInput����R���g���[���̏�Ԃ��擾
	if (XInputGetState(0, &ControllerState) == ERROR_SUCCESS)
	{
		// L�X�e�B�b�N�̒l�̎擾
		stick_L.x = static_cast<float>(ControllerState.Gamepad.sThumbLX) / 32767.0f;
		stick_L.y = static_cast<float>(ControllerState.Gamepad.sThumbLY) / 32767.0f;

		// R�X�e�B�b�N�̒l�̎擾
		stick_R.x = static_cast<float>(ControllerState.Gamepad.sThumbRX) / 32767.0f;
		stick_R.y = static_cast<float>(ControllerState.Gamepad.sThumbRY) / 32767.0f;

		// X���̃f�b�h�]�[��
		if (abs(stick_L.x) < deadZone_L.x)
		{
			stick_L.x = 0.0f;
		}

		// Y���̃f�b�h�]�[��
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


