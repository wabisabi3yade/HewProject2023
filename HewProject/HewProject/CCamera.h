#pragma once

#include "CObject.h"

#include "direct3d.h"

// ゲームのカメラのクラス
// カメラはプレイヤーを追従していく
class CCamera
	: public CObject
{
	CCamera();

	~CCamera();

	static CCamera* instance;

public:
	static float scaleScreen;	// 画像の大きさ（値が小さくなるほど画像は大きくなる）
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
		mTransform.pos.x = set.x;
		mTransform.pos.y = set.y;
	}

	// カメラの座標を取得
	//DirectX::XMFLOAT3 GetPos() { return pos; }
	Vector3 GetPos() { return mTransform.pos; }

	// カメラの回転角度（Z軸）を取得
	float GetRotZ() { return mTransform.rotation.z; }

	//拡大
	void Zoom();
	// 画像の大きさ（値が小さくなるほど画像は大きくなる）
	void Zoom(float _targetScale,float _stageScale, Vector3 _targetPos);

	//縮小
	void Reduction();
};