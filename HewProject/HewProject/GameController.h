#pragma once

#include <Windows.h>
#include <Xinput.h>
#include "Vector3.h"
#include "Vector2.h"


// �Q�[���̃R���g���[���[���Ǘ�����N���X�i�V���O���g���j
class GameController
{
	static GameController* instance;

	// LR�X�e�B�b�N�̌X���i�͈́F-1�`1�j
	Vector2 stick_L = {};
	/*Vector2 stick_R = {};*/

	Vector2 deadZone_L = {};

	// XInput�̏�����
	XINPUT_STATE ControllerState;

	GameController();

	~GameController();
public:
	// �R���g���[���[�̃C���X�^���X���擾����
	static GameController* GetInstance();
	// �C���X�^���X���폜����
	static void Delete();


	void PadStick();

	bool Button(WORD button);


	// ���̌X�����擾����
	Vector2 GetStick_L()const { return stick_L; }
	//// �E�̌X�����擾����
	//Vector2 GetStick_R()const { return stick_R; }

	void SetDeadZone_L_X(const float& _setDaeadZoneX) { deadZone_L.x = _setDaeadZoneX; }
	void SetDeadZone_L_Y(const float& _setDaeadZoneY) { deadZone_L.y = _setDaeadZoneY; }
	
private:

	
};
