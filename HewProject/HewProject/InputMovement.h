#pragma once
#include "Vector2.h"

class GameController;
// スティックの移動量とキーボードの移動を取得する
class InputMovement
{
	Vector2 keyboardMovement = Vector2::zero;

	static InputMovement* instance;	
	GameController* controller;

	InputMovement();
	~InputMovement();
public:
	static InputMovement* GetInstance();
	static void Delete();

	// キーボードの移動量を求めて変数に代入する 範囲(0.0～1.0)
	void KeybordMovementUpdate();

	// コントローラー、キーボードのスティックの移動量を取得する 範囲(0.0～1.0)
	// 優先度：コントローラー　→　キーボードの入力の順番で受け付ける
	Vector2 CheckMovement();
};

