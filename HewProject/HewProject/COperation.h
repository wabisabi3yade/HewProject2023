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

	GameController();

	~GameController();

	void PadStick();

	bool Button(WORD button);


	// ���̌X�����擾����
	Vector2 GetStick_L()const { return stick_L; }
	Vector2 GetStick_R()const { return stick_R; }

	void SetDeadZone_L_X(const float& _setDaeadZoneX) { deadZone_L.x = _setDaeadZoneX; }
	void SetDeadZone_L_Y(const float& _setDaeadZoneY) { deadZone_L.y = _setDaeadZoneY; }
	
private:

	// XInput�̏�����
	XINPUT_STATE ControllerState;
};
