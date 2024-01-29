#pragma once
#include "CInput.h"
#include "InputStateUpdate.h"
#include "InputMovement.h"

// キーボード、コントローラーでの入力を管理するクラス
class InputManager
{
	static InputManager* instance;	// インスタンス

	GameController* controller;	// コントローラークラス

	InputStateUpdate* inputStateUpdate;	// 入力状態更新クラス

	InputMovement* inputMovement;	// 入力の移動量を取得するクラス

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

	// 左スティックとキーボードの入力を取得する 範囲(0.0～1.0)
	Vector2 GetMovement();
};



