#pragma once
#include "direct3d.h"
#include "CObject.h"
#include "CInput.h"
#include "direct3d.h"
#include "Fade.h"

class CSceneManager; //マネージャのプロトタイプ宣言

// シーンの基礎クラス
class CScene
{
public:
	// シーンの名前
	enum SCENE_NAME
	{
		NONE  = -1,	// なにもなし

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

		// 1ワールド
		STAGE1_1,
		STAGE1_2,
		STAGE1_3,
		STAGE1_4,
		STAGE1_5,
		STAGE1_6,

		// 2ワールド
		STAGE2_1,
		STAGE2_2,
		STAGE2_3,
		STAGE2_4,

		// 3ワールド
		STAGE3_1,
		STAGE3_2,
		STAGE3_3,
		STAGE3_4,

		// 4ワールド
		STAGE4_1,
		STAGE4_2,
		STAGE4_3,
		STAGE4_4,
		
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

