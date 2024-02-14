#pragma once
#include "direct3d.h"
#include "CObject.h"
#include "CInput.h"
#include "direct3d.h"

class CSceneManager; //マネージャのプロトタイプ宣言

// シーンの基礎クラス
class CScene
{
public:
	// シーンの名前
	enum SCENE_NAME
	{
		KAWADA,	// 河田シーン
		TATEMIZO,	// 立溝シーン
		MIZUNO,	// 水野シーン
		WAKAMURA,	// 若村シーン
		HASHIMOTO,	// 橋本シーン
		// ↓　シーンを追加するならここに書いてね
		STAGE1,
		FADE_TEST,
		TITLE,
		GAMEOVER,
		GAMECLEAR,
		WORLD1_SELECT,
		WORLD2_SELECT,
		MENU,
		GAMESTART,
		WORLD3_SELECT,
		WORLD4_SELECT,
		LOADING,	// ローディング

		SCENE_NUM,	// シーンの数
		NONE,	// なにもなし
		SELECT,	// セレクトシーン
		HOSODA_SELECT
	};

private:
	

protected:
	// シーンマネージャー
	CSceneManager* pSceneManager = nullptr;

	int nextScene;

	// シーンを変えるフラグ
	bool isSceneChange = false;
	bool isExit = false;
public:
	CScene();

	virtual ~CScene();

	// 更新処理
	virtual void Update() = 0;

	// Updateのあとに行われる更新（カメラの更新とかはここに書く）
	virtual void LateUpdate() = 0;

	// 描画をする
	virtual void Draw() = 0;

	// シーンを変えるときに呼ぶ関数
	void SetScene(int _nextScene);

	void Exit();

	//　シーンマネージャーを変えているか確認する
	void SceneChangeCheck();

	// 終了するか確認
	void ExitCheck();

	// シーン変わるフラグを取得
	bool GetSceneChange() { return isSceneChange; }

	// 次に変えるシーンを取得
	int GetNextScene() { return nextScene; }

};

