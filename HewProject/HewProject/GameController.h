#pragma once

#include <Windows.h>
#include <Xinput.h>
#include "Vector3.h"
#include "Vector2.h"


// ゲームのコントローラーを管理するクラス（シングルトン）
class GameController
{
	static GameController* instance;

	// LRスティックの傾き（範囲：-1～1）
	Vector2 stick_L = {};
	/*Vector2 stick_R = {};*/

	Vector2 deadZone_L = {};

	// XInputの初期化
	XINPUT_STATE ControllerState;

	GameController();

	~GameController();
public:
	// コントローラーのインスタンスを取得する
	static GameController* GetInstance();
	// インスタンスを削除する
	static void Delete();


	void PadStick();

	bool Button(WORD button);


	// 左の傾きを取得する
	Vector2 GetStick_L()const { return stick_L; }
	//// 右の傾きを取得する
	//Vector2 GetStick_R()const { return stick_R; }

	void SetDeadZone_L_X(const float& _setDaeadZoneX) { deadZone_L.x = _setDaeadZoneX; }
	void SetDeadZone_L_Y(const float& _setDaeadZoneY) { deadZone_L.y = _setDaeadZoneY; }
	
private:

	
};
