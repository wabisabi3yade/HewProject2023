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
		SCENE_NUM,	// シーンの数

		SELECT,	// セレクトシーン
	};

private:
	// シーンマネージャー
	CSceneManager* pSceneManager = nullptr;

protected:
	int nextScene;

	// シーンを変えるフラグ
	bool isSceneChange = false;
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

	//　シーンマネージャーを変えているか確認する
	void SceneChangeCheck();

	// シーン変わるフラグを取得
	bool GetSceneChange() { return isSceneChange; }

	// 次に変えるシーンを取得
	int GetNextScene() { return nextScene; }

};

