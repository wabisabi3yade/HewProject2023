#pragma once
#include "Vector2.h"

class GameController;
// スティックの移動量とキーボードの移動を取得する
class InputMovement
{
	static InputMovement* instance;	

	GameController* controller;

	InputMovement();
	~InputMovement();
public:
	static InputMovement* GetInstance();
	static void Delete();

	// キーボードの移動量を求める 範囲(0.0～1.0)
	Vector2 KeybordMovement();

	// コントローラー、キーボードのスティックの移動量を取得する 範囲(0.0～1.0)
	// 優先度：コントローラー　→　キーボードの入力の順番で受け付ける
	Vector2 CheckMovement();
};

