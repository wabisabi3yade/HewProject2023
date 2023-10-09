#pragma once

#include "direct3d.h"

// ゲームのカメラのクラス
// カメラはプレイヤーを追従していく
class CCamera
{
	Vector3 pos = {};	// 座標

	float rotZ = 0.0f;	// 回転角度

	CCamera();

	~CCamera();

	static CCamera* instance;

public:
	// インスタンスをを取得
	// 初めて呼び出されたらインスタンスを生成
	static CCamera* GetInstance();

	// インスタンスを削除
	static void Delete();

	// 初期化する関数
	void Init();

	// カメラの処理
	void Update();

	// ゲッター・セッター関数
	// 座標
	void SetPos(FLOAT_XY set)
	{
		pos.x = set.x;
		pos.y = set.y;
	}

	// カメラの座標を取得
	DirectX::XMFLOAT3 GetPos() { return pos; }

	// カメラの回転角度（Z軸）を取得
	float GetRotZ() { return rotZ; }
};