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

	std::unique_ptr<DoTween> dotween;

	// 描画に使用する頂点バッファ
	static D3DBUFFER mVertexBuffer;

	// 描画に使用するテクスチャ
	static D3DTEXTURE mTexture;

	DirectX::XMFLOAT4 materialDiffuse = { 1,1,1,1 };	// マテリアル色

	// アクティブ/非アクティブ切り替え変数
	bool isActive = false;
	static bool isMakeInstance;	// インスタンスを既に作ったか

	// トランスフォーム
	Transform mTransform;

	Fade();
	~Fade();

public:
	static Fade* Get();

	void Draw();

	static void Init();

};

