#pragma once
#include "CInput.h"
#include "InputStateUpdate.h"


// �L�[�{�[�h�A�R���g���[���[�ł̓��͂��Ǘ�����N���X
class InputManager
{
	static InputManager* instance;	// �C���X�^���X

	GameController* controller;	// �R���g���[���[�N���X

	InputStateUpdate* inputStateUpdate;	// ���͏�ԍX�V�N���X

	InputManager();
	~InputManager();
public:
	static InputManager* GetInstance();

	static void Delete();

	// �{�^����Ԃ��X�V����
	void UpdateInputState();

	// �{�^��������Ă��邩
	bool GetInputPress(InputStateUpdate::TYPE _button);

	// �{�^�������ꂽ��Ԃ�
	bool GetInputTrigger(InputStateUpdate::TYPE _button);

	// �R���g���[���[�̃|�C���^
	GameController* GetController()const { return controller; }
};



