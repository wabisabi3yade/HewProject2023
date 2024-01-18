#pragma once

#include <Windows.h>
#include <Xinput.h>
#include "Vector3.h"
#include "Vector2.h"

class GameController
{
	// LR�X�e�B�b�N�̌X���i�͈́F-1�`1�j
	Vector2 stick_L = {};
	Vector2 stick_R = {};

	Vector2 deadZone_L = {};
public:

	/*//���݂̌�����\���x�N�g���ϐ�
	Vector3 dir = { 0, 0, 0 };

	//�ړ����x
	float moveSpeed = 1.0f;

	//���z���E�̒��̈ʒu���W
	Vector3 pos = { 0, 0, 0 };

	//�g��k���������ϐ�
	Vector3 scale = { 1.0f, 1.0f, 1.0f };

	//��]�p�x
	float angle = 0.0f;*/

	// �L�[����\�ȃL�����N�^�[���H
	bool isPlayer = true;

	GameController();

	~GameController();

	void GamePad();
	/*Vector3 GamePad(float stickX, float stickY);*/

	// ���̌X�����擾����
	Vector2 GetStick_L()const { return stick_L; }

	void SetDeadZone_L_X(const float& _setDaeadZoneX) { deadZone_L.x = _setDaeadZoneX; }
	void SetDeadZone_L_Y(const float& _setDaeadZoneY) { deadZone_L.y = _setDaeadZoneY; }
	/*void SetMoveSpeed(float sp)
	{
		moveSpeed = sp;
	}

	void SetDir(Vector3 v)
	{
		dir = v;
	}*/


private:

	// XInput�̏�����
	XINPUT_STATE controllerState;
};
