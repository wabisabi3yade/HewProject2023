#include "Ccontroller.h"

//静的変数
XINPUT_STATE Input::ControllerState;//コントローラーの状態

//初期化
void Input::Init() {}

//setter
//特になし！

//getter
bool Input::GetControllerDown(int _button) { return(ControllerState.Gamepad.wButtons & _button); }	//ボタンが押されたか返す
bool Input::GetController(int _button) { return(ControllerState.Gamepad.wButtons & _button); }		//ボタンが押されているか返す
bool Input::GetControllerUp(int _button) { return !(ControllerState.Gamepad.wButtons & _button); }	//ボタンが離されたか返す

//スティックの入力
//引数0or1でL,Rを判定
bool Input::GetControllerStick(int _stick)
{
	int Value=0;
	float x = 0, y = 0;


	switch (_stick)
	{
		//引数が0なら左スティック
	case 0:
		x = ControllerState.Gamepad.sThumbLX;	//左スティックのX軸
		y = ControllerState.Gamepad.sThumbLY;	//左スティックのY軸
		break;
		//引数が1なら右スティック
	case 1:
		x = ControllerState.Gamepad.sThumbRX;	//右スティックのX軸
		y = ControllerState.Gamepad.sThumbRY;	//右スティックのY軸
		break;
	};
	return Value; (x, y) / 32768;	//XInputは65535段階(-32768～327768)int型
}


//triggerの入力
//引数0or1でL,Rを判定
//コントローラのトリガーの値を返す関数
float Input::GetControllerTrigger(int _trigger)
{
	float val = 0;
	switch (_trigger)
	{
	//引数が0なら左トリガー
	case 0:
		val = (float)(ControllerState.Gamepad.bLeftTrigger) / 255;
		break;
	//引数が1なら右トリガー
	case 1:
		val = (float)(ControllerState.Gamepad.bRightTrigger) / 255;
		break;
	}
	return val;		//XInputのトリガー入力はint型で255段階(0～255)
}

//縦入力
float Input::GetVertical()
{
	float ControllerVal = GetControllerStick(0), y;	//スティックのY軸の値

	if (ControllerVal != 0)
	{
		return ControllerVal;
	}
}

//横入力
float Input::GetHorizontal()
{
	float ControllerVal = GetControllerStick(0), x;	//スティックのX軸の値
	if (ControllerVal != 0)
	{
		return ControllerVal;
	}
}

//決定
bool Input::GetDecisionDown()
{
	if (GetController(Pad_X)) { return true; }	//Aが押されたらtrueを返す
	return false;
}

//キャンセル
bool Input::GetCancelDown()
{
	if (GetController(Pad_B)) { return true; }	//Bが押されたらtrueを返す
	return false;
}

//ジャンプ
bool Input::GetJumpDown()
{
	if (GetController(Pad_A)) { return true; }
	return false;
}

//攻撃
bool Input::GetAttackDown()
{
	if (GetController(Pad_Y)) { return true; }
	return false;
}

//XInputの状態を取得し、値を格納
void Input::Update() 
{
	XInputGetState(0, &ControllerState);
}