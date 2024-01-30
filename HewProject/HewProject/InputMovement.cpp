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

void InputMovement::KeybordMovementUpdate()
{
	keyboardMovement = Vector2::zero;
	const float moveValue = 1.0f;

	// �e�ړ��L�[�������ꂽ��A���̕����Ɍ������ړ��ʂ𑫂�
	if (gInput->GetKeyPress(VK_UP))
	{
		keyboardMovement.y += moveValue;
	}

	if (gInput->GetKeyPress(VK_DOWN))
	{
		keyboardMovement.y -= moveValue;
	}

	if (gInput->GetKeyPress(VK_RIGHT))
	{
		keyboardMovement.x += moveValue;
	}

	if (gInput->GetKeyPress(VK_LEFT))
	{
		keyboardMovement.x -= moveValue;
	}
}

Vector2 InputMovement::CheckMovement()
{
	Vector2 movement = Vector2::zero;

	// �R���g���[���[�̍��X�e�B�b�N�̈ړ��ʂ��擾����
	movement = controller->GetStick_L();

	// ���X�e�B�b�N�ɓ��͂���Ă����Ȃ�
	// �L�[�{�[�h�̓��͎͂󂯕t���Ȃ�
	if (movement.x != 0.0f || movement.y != 0.0f)
		return movement;

	// �L�[�{�[�h�̓��͂��擾��;
	return keyboardMovement;
}


