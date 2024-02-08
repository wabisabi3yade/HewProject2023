#pragma once
#include "CScene.h"
#include "CEffectManeger.h"
#include "TextureFactory.h"
#include "InputManager.h"
#include "Fade.h"

//static EffectManeger* EffectMane;

// シーンを管理するクラス
class CSceneManager
{
private:
	// 終了するか確認フラグ
	bool isGameExit = false;
	CScene* pNowScene = nullptr;
	CScene::SCENE_NAME nowSceneName;
		
	EffectManeger* effectManeger;
	TextureFactory* textureFactory;
	InputManager* inputManager = nullptr;
	Fade* fade;
	
	CSceneManager();

	~CSceneManager();

	// シーンマネージャーに実体（インスタンス）
	static CSceneManager* instance;

public:
	// シーンマネージャーを取得
	// 初めて呼び出されたらインスタンスを生成
	static CSceneManager* GetInstance();

	// インスタンスを削除
	static void Delete();

	// シーンマネージャーの実行関数
	void Act();

	// シーンを設定する
	void SceneChange(int _scene);

	// シーンを設定する
	void SceneChangeStage(const wchar_t* _path);

	// ゲームを終了する
	void Exit();

	// 現在のシーンを取得
	CScene::SCENE_NAME GetNowScene();
	// 終了フラグ取得
	bool GetGameExit()const { return isGameExit; }
};

