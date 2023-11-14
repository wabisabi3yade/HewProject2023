#pragma once

#include "direct3d.h"
#include "CCamera.h"
#include "CAnimation.h"
#include"Vector3.h"
#include "Transform.h"

#define PathLength 64

enum ObjectLayer
{
	FADE,
	EFECT,
	UI,
	PLAY_GROUND,
	BACK_GROUND,
};


class CObject
{
	// カメラオブジェクト
	CCamera* mCamera;

protected:
	// 現在の向きを表すベクトル変数(3次元座標)
	Vector3 mDir = { 0, 0, 0 };

	int mLayer;

	// 移動速度
	float mMoveSpeed = 0.0f;

	// 描画に使用する頂点バッファ
	D3DBUFFER mVertexBuffer;

	// 描画に使用するテクスチャ
	D3DTEXTURE mTexture;

	// アニメーションクラス
	CAnimation* mAnim = nullptr;

	DirectX::XMFLOAT4 materialDiffuse = { 1,1,1,1 };	// マテリアル色

	// アクティブ/非アクティブ切り替え変数
	bool isActive = true;

public:

	Transform mTransform;

	//読み込むファイルのパス保存用
	const wchar_t* TexPath[PathLength];
	//Vector3 mPos = { 0, 0, 0 };	// 位置座標

	//Vector3 mScale = { 1.0f,1.0f,1.0f };	// 拡大縮小率を持つ変数

	//float mRotZ = 0.0f;	// 回転する角度を持つ変数

public:
	// メンバー関数
	// 初期化処理（コンストラクタ）
	CObject(D3DBUFFER vb, D3DTEXTURE tex);

	// ゲームループごとに実行する処理を書く関数
	virtual void Update();

	// Updateのあとに行う関数
	virtual void LateUpdate();

	// ゲームループごとに描画する処理を書く関数
	virtual void Draw();

	//ゲッター
	
	// 方向を取得
	Vector3 GetDir() { return mDir; }

	int GetLayer() { return mLayer; }


	//セッター	

	//方向を設定
	void SetDir(Vector3 setdir);

	void SetTexture(D3DTEXTURE _tex) { mTexture = _tex; }

	void SetTransformScale(Vector3 _v) { mTransform.scale = _v; }

	void SetTransformScale(float _x, float _y, float _z) {
		mTransform.scale.x = _x, mTransform.scale.y = _y, mTransform.scale.z = _z;
	}

	void SetMoveSpeed(float _moveSpeed) { mMoveSpeed = _moveSpeed; }

	void SetLayer(ObjectLayer _layer) { mLayer = _layer; }
};

