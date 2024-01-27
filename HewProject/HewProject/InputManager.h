#pragma once
#include "CInput.h"
#include "InputStateUpdate.h"


// キーボード、コントローラーでの入力を管理するクラス
class InputManager
{
	static InputManager* instance;	// インスタンス

	GameController* controller;	// コントローラークラス

	InputStateUpdate* inputStateUpdate;	// 入力状態更新クラス

	InputManager();
	~InputManager();
public:
	static InputManager* GetInstance();

	static void Delete();

	// ボタン状態を更新する
	void UpdateInputState();

	// ボタン押されているか
	bool GetInputPress(InputStateUpdate::TYPE _button);

	// ボタン押された状態か
	bool GetInputTrigger(InputStateUpdate::TYPE _button);

	// コントローラーのポインタ
	GameController* GetController()const { return controller; }
};



