#pragma once
#include "CAnimation.h"
#include "Transform.h"
#include "DotweenUI.h"

class UI
{

protected:
	bool isActive;	// 表示・非表示機能
	// uv座標を宣言
	FLOAT_XY uv = { 0,0 };

	CAnimation* mAnim;	// アニメーションクラス

	// 描画に使用する頂点バッファ
	D3DBUFFER mVertexBuffer;

	// 描画に使用するテクスチャ
	D3DTEXTURE mTexture;

public:
	Transform mTransform;	// トランスフォーム
	DirectX::XMFLOAT4 materialDiffuse = { 1,1,1,1 };	// マテリアル色

	DoTweenUI* dotween;

	UI();
	UI(D3DBUFFER vb, D3DTEXTURE tex);	// バッファ、テクスチャを設定するとき
	virtual ~UI();

	void Init();

	virtual void Update();

	virtual void Draw();	// 描画関数

	void MakeDotween();	// DoTweenを使用する場合はnewした後に呼び出す

	// 表示・非表示切り替え関数
	void SetActive(const bool& _setActive) { isActive = _setActive; }

	void SetBuffer(const D3DBUFFER _vb) { mVertexBuffer = _vb; }
	void SetTexture(const D3DTEXTURE _tex) { mTexture = _tex; }

	void SetUV(const float& _setU, const float& _setV) { uv.x = _setU; uv.y = _setV; }

};

