#pragma once
#include <iostream>
#include "direct3d.h"
#include <functional>
#include "CScene.h"

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

	bool isSceneChange = false;
	bool isLoadChange = false;

	int nextScene;	// 次のシーン

	// アクティブ/非アクティブ切り替え変数
	bool isActive;
	// ロードの時間
	float loadingTime;

	STATE state;	// フェードが今どの状態か
	STATE nextState;	// 次のフェードがどの状態か

	UI* fadeBase;	// 空オブジェクト(Fadeの全体の座標)

	// ローディング
	UI* backGround;	// 背景
	UI* nowLoading;	// テキスト
	UI* character;	// キャラクター

	std::function<void()> func = nullptr;

	Fade();
	~Fade();

	D3DTEXTURE tex;
	D3DBUFFER vb;

	void SceneChange();

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
	/// 引数① フェードインした後にする状態
	/// FADE_OUT:すぐにフェードが開ける
	/// LOADING:ローディングに入る
	/// 
	/// 引数②　フェード後のやること
	void FadeIn(const STATE& _nextState, std::function<void()> _onFunc = nullptr, 
		int _setScene = CScene::SCENE_NAME::NONE);

	// ローディングのための初期化をする
	void LoadingInit();
	// フェードアウトする
	void FadeOutInit();

	void Draw();

	// ロードシーンに遷移する
	void ChangeLoadScene();

	bool GetIsChange();

	bool GetLoadChange();
	
	// 次のシーンに移行
	int GetNextScene();

};

