#include "InputMovement.h"
#include "GameController.h"
#include "CInput.h"

InputMovement* InputMovement::instance = nullptr;

InputMovement::InputMovement()
{
	controller = GameController::GetInstance();
}

InputMovement::~InputMovement()
{
	
}

InputMovement* InputMovement::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new InputMovement();
	}

	return instance;
}

void InputMovement::Delete()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

Vector2 InputMovement::KeybordMovement()
{
	Vector2 keyMovement = Vector2::zero;
	const float moveValue = 1.0f;

	// �e�ړ��L�[�������ꂽ��A���̕����Ɍ������ړ��ʂ𑫂�
	if (gInput->GetKeyPress(VK_UP))
	{
		keyMovement.y += moveValue;
	}

	if (gInput->GetKeyPress(VK_DOWN))
	{
		keyMovement.y -= moveValue;
	}

	if (gInput->GetKeyPress(VK_RIGHT))
	{
		keyMovement.x += moveValue;
	}

	if (gInput->GetKeyPress(VK_LEFT))
	{
		keyMovement.x -= moveValue;
	}

	return keyMovement;
}

Vector2 InputMovement::CheckMovement()
{
	Vector2 movement = Vector2::zero;

	controller->PadStick();

	// �R���g���[���[�̍��X�e�B�b�N�̈ړ��ʂ��擾����
	movement = controller->GetStick_L();

	// ���X�e�B�b�N�ɓ��͂���Ă����Ȃ�
	// �L�[�{�[�h�̓��͎͂󂯕t���Ȃ�
	if (movement.x != 0.0f || movement.y != 0.0f)
		return movement;

	// ���L�[�{�[�h�̓��� ///////////////////////

	// �L�[�{�[�h�̓��͂��擾����
	movement = KeybordMovement();
	return movement;
}


