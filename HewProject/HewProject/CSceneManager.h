#pragma once
#include "CScene.h"
#include "CEffectManeger.h"
#include "TextureFactory.h"
#include "Fade.h"

//static EffectManeger* EffectMane;

// シーンを管理するクラス
class CSceneManager
{
private:
	CScene* pNowScene = nullptr;
	CScene::SCENE_NAME nowSceneName;
		
	EffectManeger* effectManeger;
	TextureFactory* textureFactory;
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

	// 現在のシーンを取得
	CScene::SCENE_NAME GetNowScene();
};

