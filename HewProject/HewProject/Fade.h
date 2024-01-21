#pragma once
#include <iostream>
#include "direct3d.h"

#define FADE_BACK_NUM (2)	// フェード背景の数

class FadeUI;
class UI;

// ゲーム全体のフェードを担うクラス
class Fade
{
public:
	// DoTweenの状態
	enum class STATE
	{
		STAY,	// 何もしていない状態
		FADE_IN,	// フェードが入ってくる
		LOADING, // ローディング
		FADE_OUT,
	};

private:
	static Fade* instance;

	// アクティブ/非アクティブ切り替え変数
	bool isActive;

	// ロードの時間
	float loadingTime;

	STATE state;	// フェードが今どの状態か
	STATE nextState;	// 次のフェードがどの状態か

	UI* fadeBase;	// 空オブジェクト(Fadeの全体の座標)
	FadeUI* backGround[FADE_BACK_NUM];	// 背景

	Fade();
	~Fade();

	D3DTEXTURE tex;
	D3DBUFFER vb;

public:
	static Fade* GetInstance();

	static void Delete();

	void Update();

	void FadeInUpdate();
	void LoadingUpdate();
	void FadeOutUpdate();

	/// <summary>
	/// フェードインする関数
	/// </summary>
	/// 引数 フェードインした後にする状態
	/// FADE_OUT:すぐにフェードが開ける
	/// LOADING:ローディングに入る
	void FadeIn(const STATE& _nextState);

	// ローディングのための初期化をする
	void LoadingInit();
	// フェードアウトする
	void FadeOutInit();

	void Draw();
};

