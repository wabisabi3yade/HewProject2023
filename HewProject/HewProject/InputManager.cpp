#include "InputManager.h"
#include "GameController.h"
#include "InputStateUpdate.h"

InputManager* InputManager::instance = nullptr;

InputManager::InputManager()
{
	controller = GameController::GetInstance();
	inputStateUpdate = InputStateUpdate::GetInstance();
	inputMovement = InputMovement::GetInstance();
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

void InputManager::UpdateInputState()
{
	inputStateUpdate->UpdateKeyState();
}

bool InputManager::GetInputPress(InputStateUpdate::TYPE _button)
{
	return inputStateUpdate->GetInputPress(_button);
}

bool InputManager::GetInputTrigger(InputStateUpdate::TYPE _button)
{
	return  inputStateUpdate->GetInputTrigger(_button);
}

Vector2 InputManager::GetMovement()
{
	return inputMovement->CheckMovement();
}


