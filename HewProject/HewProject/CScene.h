#pragma once
#include "direct3d.h"
#include "CObject.h"
#include "CInput.h"
#include "direct3d.h"

class CSceneManager; //マネージャのプロトタイプ宣言

// シーンの基礎クラス
class CScene
{

	// シーンマネージャー
	CSceneManager* pSceneManager = nullptr;

protected:
	int nextScene;

	// シーンを変えるフラグ
	bool isSceneChange = false;
public:
	CScene();

	~CScene();

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

