#pragma once
#include "GameController.h"

namespace InputType
{
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
}


class InputStateUpdate
{
public:
	// �^�C�v�̐�
	const short int typeNum = static_cast<short int>(InputType::TYPE::NUM);

private:
	static InputStateUpdate* instance;

	bool c_InputState[static_cast<int>(InputType::TYPE::NUM)] = {};	// ���݂̃{�^���̓��͏��
	bool o_InputState[static_cast<int>(InputType::TYPE::NUM)] = {};	// 1�t���[���O�̃{�^���̓��͏��

	// CInput�ŏ�L�{�^���^�C�v�ɑΉ������L�[��ۊ�
	int cInput_Support[static_cast<int>(InputType::TYPE::NUM)] = {};

	// GameController�ŏ�L�{�^���^�C�v�ɑΉ������{�^����ۊ�
	WORD contoroller_Support[static_cast<int>(InputType::TYPE::NUM)] = {};

	GameController* controller = nullptr;	// �R���g���[���[�N���X

	InputStateUpdate();
	~InputStateUpdate();
public:
	static InputStateUpdate* GetInstance();
	static void Delete();

	void UpdateKeyState();

	bool GetInputPress(InputType::TYPE _buttonType);
	bool GetInputTrigger(InputType::TYPE _buttonType);
};
