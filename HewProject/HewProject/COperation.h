#pragma once

#include <Windows.h>
#include <Xinput.h>
#include "Vector3.h"

class GameController
{
public:

	//現在の向きを表すベクトル変数
	Vector3 dir = { 0, 0, 0 };

	//移動速度
	float moveSpeed = 1.0f;

	// キー操作可能なキャラクターか？
	bool isPlayer = true;

	//仮想世界の中の位置座標
	Vector3 pos = { 0, 0, 0 };

	//拡大縮小率を持つ変数
	Vector3 scale = { 1.0f, 1.0f, 1.0f };

	//回転角度
	float angle = 0.0f;


	GameController();

	~GameController();


	Vector3 GamePad();

	void SetMoveSpeed(float sp)
	{
		moveSpeed = sp;
	}

	void SetDir(Vector3 v)
	{
		dir = v;
	}


private:
	XINPUT_STATE m_controllerState;

	// XInputの初期化
	XINPUT_STATE controllerState;

	// スティックの値を格納する変数
	float m_leftStickX;
	float m_leftStickY;
	float m_rightStickX;
	float m_rightStickY;
};
