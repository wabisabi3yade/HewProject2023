#pragma once
#include <iostream>
#include "direct3d.h"
#include "Transform.h"
class DoTween;

// ゲーム全体のフェードを担うクラス
class Fade
{
	// DoTweenの状態
	enum class STATE
	{
		STAY,	// 何もしていない状態
		FADE_IN,	// フェードが入ってくる
		STOP, // 真ん中で止まっている状態
		FADE_OUT,
	};

	static Fade* instance;

	// アクティブ/非アクティブ切り替え変数
	bool isActive = false;

	// 描画に使用する頂点バッファ
	D3DBUFFER mVertexBuffer;

	// 描画に使用するテクスチャ
	D3DTEXTURE mTexture;

	DirectX::XMFLOAT4 materialDiffuse = { 1,1,1,1 };	// マテリアル色

	// トランスフォーム
	Transform mTransform;

	Fade();
	~Fade();

public:
	static Fade* GetInstance();

	static void Delete();

	void Update();

	void Draw();
};

