#include "COperation.h"
#include  <iostream>

#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  30000

//�R�����g

GameController::GameController()
{
}

GameController::~GameController()
{
}

void GameController::GamePad()
{
	// XInput����R���g���[���̏�Ԃ��擾
	if (XInputGetState(0, &controllerState) == ERROR_SUCCESS)
	{
		// �X�e�B�b�N�̒l�̎擾
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

		//// �f�b�h�]�[���ȓ��̓��͂Ȃ�
		//if (abs(stick_L.x) < 0.95 && abs(stick_L.y) < 0.95)
		//{
		//	// �X�e�B�b�N�̌X��0�ɂ���s
		//	stick_L = {};
		//}
	}

	return;
}

//Vector3 GameController::GamePad(float stickX, float stickY)
//{
//
//
//		// XInput����R���g���[���̏�Ԃ��擾
//	if (XInputGetState(0, &controllerState) == ERROR_SUCCESS)
//	{
//		// �X�e�B�b�N�̒l�̎擾
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
//				d.y = -1;// �������x�N�g��
//				moveSpeed = 0.01f;
//			}
//		}*/
//
//}