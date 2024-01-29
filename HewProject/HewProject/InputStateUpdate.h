#pragma once
#include "GameController.h"

class InputStateUpdate
{
public:
	enum TYPE
	{
		DECIDE,	// ����
		CANCEL,	// �L�����Z��
		OPTION,	// �X�^�[�g
		CAMERA,	// �}�b�v���ŃJ�������[�h�ɐ؂�ւ���
		L_BUTTON,	// L�{�^��
		R_BUTTON,	// R�{�^��
		NUM
	};

	// �^�C�v�̐�
	const short int typeNum = static_cast<short int>(TYPE::NUM);

private:
	static InputStateUpdate* instance;

	bool c_InputState[static_cast<int>(TYPE::NUM)] = {};	// ���݂̃{�^���̓��͏��
	bool o_InputState[static_cast<int>(TYPE::NUM)] = {};	// 1�t���[���O�̃{�^���̓��͏��

	// CInput�ŏ�L�{�^���^�C�v�ɑΉ������L�[��ۊ�
	int cInput_Support[static_cast<int>(TYPE::NUM)] = {};

	// GameController�ŏ�L�{�^���^�C�v�ɑΉ������{�^����ۊ�
	WORD contoroller_Support[static_cast<int>(TYPE::NUM)] = {};

	GameController* controller = nullptr;	// �R���g���[���[�N���X

	InputStateUpdate();
	~InputStateUpdate();
public:
	static InputStateUpdate* GetInstance();
	static void Delete();

	void UpdateKeyState();

	bool GetInputPress(TYPE _buttonType);
	bool GetInputTrigger(TYPE _buttonType);
};
