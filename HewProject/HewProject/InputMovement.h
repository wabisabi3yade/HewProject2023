#pragma once
#include "Vector2.h"

class GameController;
// �X�e�B�b�N�̈ړ��ʂƃL�[�{�[�h�̈ړ����擾����
class InputMovement
{
	Vector2 keyboardMovement = Vector2::zero;

	static InputMovement* instance;	
	GameController* controller;

	InputMovement();
	~InputMovement();
public:
	static InputMovement* GetInstance();
	static void Delete();

	// �L�[�{�[�h�̈ړ��ʂ����߂ĕϐ��ɑ������ �͈�(0.0�`1.0)
	void KeybordMovementUpdate();

	// �R���g���[���[�A�L�[�{�[�h�̃X�e�B�b�N�̈ړ��ʂ��擾���� �͈�(0.0�`1.0)
	// �D��x�F�R���g���[���[�@���@�L�[�{�[�h�̓��͂̏��ԂŎ󂯕t����
	Vector2 CheckMovement();
};

