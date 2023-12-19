#pragma once
#pragma comment (lib, "xinput.lib")
#pragma comment (lib, "dinput8.lib")

#define DIRECTINPUT_VERSION 0x0800

#include <Windows.h>
#include <Xinput.h>
#include <Dinput.h>
#include "Vector3.h"

class Input
{
	//�R���g���[���[�̏�Ԃ�\��
	static XINPUT_STATE ControllerState;	//���̃R���g���[���[�̏��
	static XINPUT_STATE FControllerState;	//�O�t���[���̃R���g���[���[�̏��

	int* gValue = 0;

public:

	//setter
	//setter�͓��ɂȂ��I

	//Getter
	static bool	 GetControllerDown(int);		//�{�^���������ꂽ��
	static bool  GetController(int);			//�{�^����������Ă��邩
	static bool  GetControllerUp(int);			//�{�^���������ꂽ��
	static Vector3  GetControllerStick(int);	//�X�e�B�b�N
	static float GetControllerTrigger(int);		//trigger(LT,RT)

	//����
	static float GetVertical();			//�c����
	static float GetHorizontal();		//������
	static bool FDpadVertical;
	static bool GetDpadVerticaldown();	//�\���L�[�̏c����
	static bool GetDpadVertical();
	static bool FDpadHorizontal;
	static bool GetDpadHorizontalDown();//�\���L�[�̉�����
	static bool GetDpadHorizontal();
	static bool FDecision;
	static bool GetDecisionDown();		//�������
	static bool GetDecision();
	static bool FCancel;
	static bool GetCancelDown();		//�L�����Z��
	static bool GetCancel();
	static bool GetJumpDown();			//�W�����v
	static bool GetAttackDown();		//�U��

	//�X�V
	static void Update();
};

enum GAME_PAD
{
	Pad_UP = XINPUT_GAMEPAD_DPAD_UP,				//�\���L�[��
	Pad_DOWN = XINPUT_GAMEPAD_DPAD_DOWN,			//�\���L�[��
	Pad_L = XINPUT_GAMEPAD_DPAD_LEFT,				//�\���L�[��
	Pad_R = XINPUT_GAMEPAD_DPAD_RIGHT,				//�\���L�[�E
	Pad_START = XINPUT_GAMEPAD_START,				//start	
	Pad_BACK = XINPUT_GAMEPAD_BACK,					//back
	Pad_L_THUMB = XINPUT_GAMEPAD_LEFT_THUMB,		//���X�e�B�b�N
	Pad_R_THUMB = XINPUT_GAMEPAD_RIGHT_THUMB,		//�E�X�e�B�b�N
	Pad_L_SHOULDER = XINPUT_GAMEPAD_LEFT_SHOULDER,	//LB
	Pad_R_SHOULDER = XINPUT_GAMEPAD_RIGHT_SHOULDER,	//RB
	Pad_A = XINPUT_GAMEPAD_A,						//A�{�^��
	Pad_B = XINPUT_GAMEPAD_B,						//B�{�^��
	Pad_X = XINPUT_GAMEPAD_X,						//X�{�^��
	Pad_Y = XINPUT_GAMEPAD_Y,						//Y�{�^��
};