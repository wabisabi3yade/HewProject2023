#pragma once

#include <Windows.h>
#include <Xinput.h>
#include "Vector3.h"
#include "Vector2.h"

class GameController
{
	// LRスティックの傾き（範囲：-1～1）
	Vector2 stick_L = {};
	Vector2 stick_R = {};

	Vector2 deadZone_L = {};
public:

	/*//現在の向きを表すベクトル変数
	Vector3 dir = { 0, 0, 0 };

	//移動速度
	float moveSpeed = 1.0f;

	//仮想世界の中の位置座標
	Vector3 pos = { 0, 0, 0 };

	//拡大縮小率を持つ変数
	Vector3 scale = { 1.0f, 1.0f, 1.0f };

	//回転角度
	float angle = 0.0f;*/

	// キー操作可能なキャラクターか？
	bool isPlayer = true;

	GameController();

	~GameController();

	void GamePad();
	/*Vector3 GamePad(float stickX, float stickY);*/

	// 左の傾きを取得する
	Vector2 GetStick_L()const { return stick_L; }

	void SetDeadZone_L_X(const float& _setDaeadZoneX) { deadZone_L.x = _setDaeadZoneX; }
	void SetDeadZone_L_Y(const float& _setDaeadZoneY) { deadZone_L.y = _setDaeadZoneY; }
	/*void SetMoveSpeed(float sp)
	{
		moveSpeed = sp;
	}

	void SetDir(Vector3 v)
	{
		dir = v;
	}*/


private:

	// XInputの初期化
	XINPUT_STATE controllerState;
};
