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
		// ����Őݒ肷��p�̃x�N�g���ϐ�
		Vector3 d = { 0.0f,0.0f,0.0f };

		// �ړ����x�����߂ɂO�ɂ���
		moveSpeed = 0.0f;

		dir = { 0,0,0 };

		if (XInputGetState(0, &m_controllerState) == ERROR_SUCCESS)
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
				d.x = 1;//�E�����x�N�g��
				moveSpeed = 0.01f;
			}
			if (m_controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
			{
				d.y = 1;// ������x�N�g��
				moveSpeed = 0.01f;
			}
		}
		// �L�[����Ńx�N�g�����ݒ肳��Ă�����dir�ɑ������
		if (d.x != 0.0f || d.y != 0.0f)
		{
			dir = d;
		}
	}
	// �x�N�g�����g���Ĉړ�
	pos.x = pos.x + dir.x * moveSpeed;
	pos.y = pos.y + dir.y * moveSpeed;
	pos.z = pos.z + dir.z * moveSpeed;
}