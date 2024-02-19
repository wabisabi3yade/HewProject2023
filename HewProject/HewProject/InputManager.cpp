#include "InputManager.h"
#include "GameController.h"
#include "InputStateUpdate.h"

InputManager* InputManager::instance = nullptr;

InputManager::InputManager()
{
	controller = GameController::GetInstance();
	inputStateUpdate = InputStateUpdate::GetInstance();
	inputMovement = InputMovement::GetInstance();

	// 仮でデッドゾーン設定
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
	// ボタン入力の状態を更新する
	inputStateUpdate->UpdateKeyState();

	// コントローラーの左スティックの更新
	controller->PadStick();

	// キーボードの移動量の更新
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


