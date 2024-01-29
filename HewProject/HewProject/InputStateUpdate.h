#pragma once
#include "GameController.h"

class InputStateUpdate
{
public:
	enum TYPE
	{
		DECIDE,	// 決定
		CANCEL,	// キャンセル
		OPTION,	// スタート
		CAMERA,	// マップ中でカメラモードに切り替える
		L_BUTTON,	// Lボタン
		R_BUTTON,	// Rボタン
		NUM
	};

	// タイプの数
	const short int typeNum = static_cast<short int>(TYPE::NUM);

private:
	static InputStateUpdate* instance;

	bool c_InputState[static_cast<int>(TYPE::NUM)] = {};	// 現在のボタンの入力状態
	bool o_InputState[static_cast<int>(TYPE::NUM)] = {};	// 1フレーム前のボタンの入力状態

	// CInputで上記ボタンタイプに対応したキーを保管
	int cInput_Support[static_cast<int>(TYPE::NUM)] = {};

	// GameControllerで上記ボタンタイプに対応したボタンを保管
	WORD contoroller_Support[static_cast<int>(TYPE::NUM)] = {};

	GameController* controller = nullptr;	// コントローラークラス

	InputStateUpdate();
	~InputStateUpdate();
public:
	static InputStateUpdate* GetInstance();
	static void Delete();

	void UpdateKeyState();

	bool GetInputPress(TYPE _buttonType);
	bool GetInputTrigger(TYPE _buttonType);
};
