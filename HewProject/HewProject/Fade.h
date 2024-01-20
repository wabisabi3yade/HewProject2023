#pragma once
#include <iostream>
#include "direct3d.h"
#include "Transform.h"

class CObject;
class DoTween;

// ゲーム全体のフェードを担うクラス
class Fade
{
	// DoTweenの状態
	enum class STATE
	{
		STAY,	// 何もしていない状態
		FADE_IN,	// フェードが入ってくる
		LOADING, // ローディング
		FADE_OUT,
	};

	static Fade* instance;

	// アクティブ/非アクティブ切り替え変数
	bool isActive = false;

	// フェードが今度の状態か
	STATE state;

	// 描画に使用する頂点バッファ
	D3DBUFFER mVertexBuffer;

	// 描画に使用するテクスチャ
	D3DTEXTURE mTexture;

	DirectX::XMFLOAT4 materialDiffuse = { 1,1,1,1 };	// マテリアル色

	// トランスフォーム
	CObject* empty;

	Fade();
	~Fade();

public:
	static Fade* GetInstance();

	static void Delete();

	void Update();
	void StayUpdate();
	void FadeInUpdate();
	void LoadingUpdate();
	void FadeOutUpdate();

	void Draw();
};

