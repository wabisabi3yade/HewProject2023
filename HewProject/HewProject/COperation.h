#pragma once

#include <Xinput.h>
#include <Windows.h>
#include "Vector3.h"

class GameController
{
public:

	//���݂̌�����\���x�N�g���ϐ�
	Vector3 dir = { 0, 0, 0 };

	//�ړ����x
	float moveSpeed = 1.0f;

	// �L�[����\�ȃL�����N�^�[���H
	bool isPlayer = false;

	//���z���E�̒��̈ʒu���W
	Vector3 pos = { 0, 0, 0 };

	//�g��k���������ϐ�
	Vector3 scale = { 1.0f, 1.0f, 1.0f };

	//��]�p�x
	float angle = 0.0f;


	GameController();

	~GameController();

	void Update();

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
};
