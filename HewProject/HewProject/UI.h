#pragma once
#include "CAnimation.h"
#include "Transform.h"

class UI
{

protected:
	bool isActive;	// 表示・非表示機能
	CAnimation* mAnim;	// アニメーションクラス

	Transform mTransform;	// トランスフォーム

	// 描画に使用する頂点バッファ
	D3DBUFFER mVertexBuffer;

	// 描画に使用するテクスチャ
	D3DTEXTURE mTexture;

public:
	UI();
	UI(D3DBUFFER vb, D3DTEXTURE tex);	// バッファ、テクスチャを設定するとき
	virtual ~UI();
	
	void Init();

	virtual void Draw() = 0;	// 描画関数

	// 表示・非表示切り替え関数
	void SetActive(const bool& _setActive) { isActive = _setActive; }

	void SetBuffer(const D3DBUFFER _vb) { mVertexBuffer = _vb; }
	void SetTexture(const D3DTEXTURE _tex) { mTexture = _tex; }

};

