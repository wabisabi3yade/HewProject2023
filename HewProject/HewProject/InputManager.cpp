#include "InputManager.h"
#include "GameController.h"
#include "InputStateUpdate.h"

InputManager* InputManager::instance = nullptr;

InputManager::InputManager()
{
	controller = GameController::GetInstance();
	inputStateUpdate = InputStateUpdate::GetInstance();
	inputMovement = InputMovement::GetInstance();

	// ���Ńf�b�h�]�[���ݒ�
	Vector2 setDeadZone = { 0.5f,0.5f };
	SetDeadZone(setDeadZone);
}

InputManager::~InputManager()
{
	GameController::Delete();
	InputStateUpdate::Delete();
	InputMovement::Delete();
}

InputManager* InputManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new InputManager();
	}

	return instance;
}

void InputManager::Delete()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void InputManager::Update()
{
	// �{�^�����͂̏�Ԃ��X�V����
	inputStateUpdate->UpdateKeyState();

	// �R���g���[���[�̍��X�e�B�b�N�̍X�V
	controller->PadStick();

	// �L�[�{�[�h�̈ړ��ʂ̍X�V
	inputMovement->KeybordMovementUpdate();	
}

bool InputManager::GetInputPress(InputType::TYPE _button)
{
	return inputStateUpdate->GetInputPress(_button);
}

bool InputManager::GetInputTrigger(InputType::TYPE _button)
{
	return  inputStateUpdate->GetInputTrigger(_button);
}

void InputManager::SetDeadZone(const Vector2& _deadzone)
{
	controller->SetDeadZone_L_X(_deadzone.x);
	controller->SetDeadZone_L_Y(_deadzone.y);
}

Vector2 InputManager::GetMovement()
{
	return inputMovement->CheckMovement();
}


