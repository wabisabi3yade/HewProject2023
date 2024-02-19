#include "InputStateUpdate.h"
#include "CInput.h"

InputStateUpdate* InputStateUpdate::instance = nullptr;

InputStateUpdate::InputStateUpdate()
{
	controller = GameController::GetInstance();

	for (int i = 0; i < static_cast<int>(InputType::NUM); i++)
	{
		// 作業用変数
		int keyWork = 0;	
		WORD controllerWork = 0;

		// 各ボタンタイプに対応したキーとコントローラーを決定する
		switch (static_cast<InputType::TYPE>(i))
		{
		case InputType::DECIDE:
			keyWork = VK_SPACE;
			controllerWork = XINPUT_GAMEPAD_A;
			break;

		case InputType::CANCEL:
			keyWork = VK_BACK;
			controllerWork = XINPUT_GAMEPAD_B;
			break;

		case InputType::OPTION:
			keyWork = VK_TAB;
			controllerWork = XINPUT_GAMEPAD_START;
			break;

		case InputType::CAMERA:
			keyWork = VK_CONTROL;
			controllerWork = XINPUT_GAMEPAD_Y;
			break;

		case InputType::L_BUTTON:
			keyWork = VK_F11;
			controllerWork = XINPUT_GAMEPAD_LEFT_SHOULDER;
			break;

		case InputType::R_BUTTON:
			keyWork = VK_F12;
			controllerWork = XINPUT_GAMEPAD_RIGHT_SHOULDER;
			break;

		case InputType::Undo:
			keyWork = VK_DELETE;
			controllerWork = XINPUT_GAMEPAD_X;
			break;

		default:
			MessageBoxA(NULL, "対応できていないボタンタイプがあります", "エラー", MB_ICONERROR | MB_OK);
			break;
		}

		// 対応したキーを代入する
		cInput_Support[i] = keyWork;
		contoroller_Support[i] = controllerWork;
	}
}

InputStateUpdate::~InputStateUpdate()
{
}

InputStateUpdate* InputStateUpdate::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new InputStateUpdate();
	}

	return instance;
}

void InputStateUpdate::Delete()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void InputStateUpdate::UpdateKeyState()
{	
	// 前フレームの状態を更新する
	// 指定バイト数分メモリをコピーする関数
	memcpy_s(o_InputState, sizeof(o_InputState), c_InputState, sizeof(c_InputState));
	for (int i = 0; i < typeNum; i++)
		o_InputState[i] = c_InputState[i];

	// 今フレームの状態を更新する
	// ボタンタイプの数だけ
	for (int i = 0; i < typeNum; i++)
	{
		// 最初にフラグを降ろす
		c_InputState[i] = false;
		// キーボード、コントローラーどちらかが対応したボタンを押されていたら
		if (gInput->GetKeyPress(cInput_Support[i]) == true ||
			controller->Button(contoroller_Support[i]) == true)
		{
			// フラグを立てる
			c_InputState[i] = true;
		}
	}
}

bool InputStateUpdate::GetInputPress(InputType::TYPE _buttonType)
{
	return c_InputState[static_cast<int>(_buttonType)];
}

bool InputStateUpdate::GetInputTrigger(InputType::TYPE _buttonType)
{
	// 前フレームが押されていない　かつ　今フレームで押されている
	return !o_InputState[static_cast<int>(_buttonType)] && 
		c_InputState[static_cast<int>(_buttonType)];
}

