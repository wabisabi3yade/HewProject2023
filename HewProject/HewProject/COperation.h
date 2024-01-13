#pragma once

#include <Windows.h>
#include <Xinput.h>
#include "Vector3.h"

class GameController
{
public:

	//���݂̌�����\���x�N�g���ϐ�
	Vector3 dir = { 0, 0, 0 };

	//�ړ����x
	float moveSpeed = 1.0f;

	// �L�[����\�ȃL�����N�^�[���H
	bool isPlayer = true;

	//���z���E�̒��̈ʒu���W
	Vector3 pos = { 0, 0, 0 };

	//�g��k���������ϐ�
	Vector3 scale = { 1.0f, 1.0f, 1.0f };

	//��]�p�x
	float angle = 0.0f;


	GameController();

	~GameController();


	Vector3 GamePad();

	void SetMoveSpeed(float sp)
	{
		moveSpeed = sp;
	}

	void SetDir(Vector3 v)
	{
		dir = v;
	}


private:
	XINPUT_STATE m_controllerState;

	// XInput�̏�����
	XINPUT_STATE controllerState;

	// �X�e�B�b�N�̒l���i�[����ϐ�
	float m_leftStickX;
	float m_leftStickY;
	float m_rightStickX;
	float m_rightStickY;
};
