#include "GameController.h"
#include  <iostream>

#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  30000

// �C���X�^���X��������
GameController* GameController::instance = nullptr;

// �R�����g�ł�����

GameController::GameController()
{
	ZeroMemory(&ControllerState, sizeof(XINPUT_STATE));
}

GameController::~GameController()
{
}

GameController* GameController::GetInstance()
{
	// �C���X�^���X���擾����s
	if (instance == nullptr)
	{
		instance = new GameController();
	}

	// �C���X�^���X��Ԃ�
	return instance;
}

void GameController::Delete()
{
	// �C���X�^���X���폜����
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void GameController::PadStick()
{
	// �ŏ��ɏ���������
	stick_L = Vector2::zero;

	// XInput����R���g���[���̏�Ԃ��擾
	if (XInputGetState(0, &ControllerState) == ERROR_SUCCESS)
	{
		// L�X�e�B�b�N�̒l�̎擾
		stick_L.x = static_cast<float>(ControllerState.Gamepad.sThumbLX) / 32767.0f;
		stick_L.y = static_cast<float>(ControllerState.Gamepad.sThumbLY) / 32767.0f;

		//// R�X�e�B�b�N�̒l�̎擾
		//stick_R.x = static_cast<float>(ControllerState.Gamepad.sThumbRX) / 32767.0f;
		//stick_R.y = static_cast<float>(ControllerState.Gamepad.sThumbRY) / 32767.0f;

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


