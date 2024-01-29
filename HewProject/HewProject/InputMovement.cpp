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

	// 各移動キーが押されたら、その方向に向けた移動量を足す
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

	// コントローラーの左スティックの移動量を取得する
	movement = controller->GetStick_L();

	// 左スティックに入力されていたなら
	// キーボードの入力は受け付けない
	if (movement.x != 0.0f || movement.y != 0.0f)
		return movement;

	// ↓キーボードの入力 ///////////////////////

	// キーボードの入力を取得する
	movement = KeybordMovement();
	return movement;
}


