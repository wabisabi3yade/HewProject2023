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
		// ����Őݒ肷��p�̃x�N�g���ϐ�
		Vector3 d = { 0.0f,0.0f,0.0f };

		// �ړ����x�����߂ɂO�ɂ���
		moveSpeed = 0.0f;

		dir = { 0,0,0 };

		// XInput����R���g���[���̏�Ԃ��擾
		if (XInputGetState(0, &controllerState) == ERROR_SUCCESS)
		{
			// �X�e�B�b�N�̒l�̎擾
			float stickX = static_cast<float>(controllerState.Gamepad.sThumbLX) / 32767.0f;
			float stickY = static_cast<float>(controllerState.Gamepad.sThumbLY) / 32767.0f;

			// �ړ��x�̐ݒ�
			float sensitivity = 2.0f;
			float moveX = stickX * sensitivity;
			float moveY = stickY * sensitivity;

			//�E��
  			if ((moveX <= 2) && (moveX > 1) && (moveY >= 1))
			{
				d.y = 1;// ������x�N�g��
				moveSpeed = 0.01f;

				d.x = 1;// �E�����x�N�g��
				moveSpeed = 0.01f;
			}
			//�E��
			if ((moveX >= 1) && (moveY > -2) && (moveY < -1))
			{
				d.y = -1;// ������x�N�g��
				moveSpeed = 0.01f;

				d.x = 1;// �E�����x�N�g��
				moveSpeed = 0.01f;
			}
			//����
			if ((moveX < 0) && (moveY < 0))
			{
				d.y = -1;// ������x�N�g��
				moveSpeed = 0.01f;

				d.x = -1;// �E�����x�N�g��
				moveSpeed = 0.01f;
			}
			//����
			if ((moveX < 0) && (moveY > 1))
			{
				d.y = 1;// ������x�N�g��
				moveSpeed = 0.01f;

				d.x = -1;// �E�����x�N�g��
				moveSpeed = 0.01f;
			}
		
		}

		/*if (XInputGetState(0, &m_controllerState) == ERROR_SUCCESS)
		{
			if (m_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
			{
				d.y = -1;// �������x�N�g��
				moveSpeed = 0.01f;
			}
			if (m_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_X)
			{
				d.x = -1;// �������x�N�g��
				moveSpeed = 0.01f;
			}
			if (m_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
			{
				d.x = 1;// �E�����x�N�g��
				moveSpeed = 0.01f;
			}
			if (m_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
			{
				d.y = 1;// ������x�N�g��
				moveSpeed = 0.01f;
			}
		}*/

		// �L�[����Ńx�N�g�����ݒ肳��Ă�����dir�ɑ������
		if (d.x != 0.0f || d.y != 0.0f)
		{
			dir = d;
		}

		return d;
	}
	// �x�N�g�����g���Ĉړ�
	pos.x = pos.x + dir.x * moveSpeed;
	pos.y = pos.y + dir.y * moveSpeed;
	pos.z = pos.z + dir.z * moveSpeed;

	
}