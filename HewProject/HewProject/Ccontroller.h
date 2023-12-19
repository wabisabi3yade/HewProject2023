#pragma once
#pragma comment (lib, "xinput.lib")
#pragma comment (lib, "dinput8.lib")

#define DIRECTINPUT_VERSION 0x0800

#include <Windows.h>
#include <Xinput.h>
#include <Dinput.h>
#include "Vector3.h"

class Input
{
	//コントローラーの状態を表す
	static XINPUT_STATE ControllerState;	//今のコントローラーの状態
	static XINPUT_STATE FControllerState;	//前フレームのコントローラーの状態

	int* gValue = 0;

public:

	//setter
	//setterは特になし！

	//Getter
	static bool	 GetControllerDown(int);		//ボタンが押されたか
	static bool  GetController(int);			//ボタンが押されているか
	static bool  GetControllerUp(int);			//ボタンが離されたか
	static Vector3  GetControllerStick(int);	//スティック
	static float GetControllerTrigger(int);		//trigger(LT,RT)

	//入力
	static float GetVertical();			//縦入力
	static float GetHorizontal();		//横入力
	static bool FDpadVertical;
	static bool GetDpadVerticaldown();	//十字キーの縦入力
	static bool GetDpadVertical();
	static bool FDpadHorizontal;
	static bool GetDpadHorizontalDown();//十字キーの横入力
	static bool GetDpadHorizontal();
	static bool FDecision;
	static bool GetDecisionDown();		//決定入力
	static bool GetDecision();
	static bool FCancel;
	static bool GetCancelDown();		//キャンセル
	static bool GetCancel();
	static bool GetJumpDown();			//ジャンプ
	static bool GetAttackDown();		//攻撃

	//更新
	static void Update();
};

enum GAME_PAD
{
	Pad_UP = XINPUT_GAMEPAD_DPAD_UP,				//十字キー上
	Pad_DOWN = XINPUT_GAMEPAD_DPAD_DOWN,			//十字キー下
	Pad_L = XINPUT_GAMEPAD_DPAD_LEFT,				//十字キー左
	Pad_R = XINPUT_GAMEPAD_DPAD_RIGHT,				//十字キー右
	Pad_START = XINPUT_GAMEPAD_START,				//start	
	Pad_BACK = XINPUT_GAMEPAD_BACK,					//back
	Pad_L_THUMB = XINPUT_GAMEPAD_LEFT_THUMB,		//左スティック
	Pad_R_THUMB = XINPUT_GAMEPAD_RIGHT_THUMB,		//右スティック
	Pad_L_SHOULDER = XINPUT_GAMEPAD_LEFT_SHOULDER,	//LB
	Pad_R_SHOULDER = XINPUT_GAMEPAD_RIGHT_SHOULDER,	//RB
	Pad_A = XINPUT_GAMEPAD_A,						//Aボタン
	Pad_B = XINPUT_GAMEPAD_B,						//Bボタン
	Pad_X = XINPUT_GAMEPAD_X,						//Xボタン
	Pad_Y = XINPUT_GAMEPAD_Y,						//Yボタン
};