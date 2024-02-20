#pragma once
#include "CInput.h"
#include "InputStateUpdate.h"
#include "InputMovement.h"
#include "ControllerVibration.h"

// �L�[�{�[�h�A�R���g���[���[�ł̓��͂��Ǘ�����N���X
class InputManager
{
	static InputManager* instance;	// �C���X�^���X

	GameController* controller;	// �R���g���[���[�N���X

	InputStateUpdate* inputStateUpdate;	// ���͏�ԍX�V�N���X

	InputMovement* inputMovement;	// ���͂̈ړ��ʂ��擾����N���X

	ControllerVibration* viberation;

	InputManager();
	~InputManager();
public:
	static InputManager* GetInstance();

	static void Delete();

	void Update();

	// �{�^��������Ă��邩
	bool GetInputPress(InputType::TYPE _button);

	// �{�^�������ꂽ��Ԃ�
	bool GetInputTrigger(InputType::TYPE _button);

	// �f�b�h�]�[���i�X�e�B�b�N�̗V�т�ݒ肷��j
	void SetDeadZone(const Vector2& _deadzone);

	// �R���g���[���[�̃|�C���^
	GameController* GetController()const { return controller; }

	// ���X�e�B�b�N�ƃL�[�{�[�h�̓��͂��擾���� �͈�(0.0�`1.0)
	Vector2 GetMovement();

	void Vibelation(float _high, float _low, float _time);
};



