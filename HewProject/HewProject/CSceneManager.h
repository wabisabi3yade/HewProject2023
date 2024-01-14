#pragma once
#include "CScene.h"
#include "CEffectManeger.h"
#include "TextureFactory.h"

//static EffectManeger* EffectMane;

// シーンを管理するクラス
class CSceneManager
{

public :
	// シーンの名前
	enum SCENE_NAME
	{
		KAWADA,	// 河田シーン
		TATEMIZO,	// 立溝シーン
		MIZUNO,	// 水野シーン
		WAKAMURA,	// 若村シーン
		HASHIMOTO,	// 橋本シーン
		// ↓　シーンを追加するならここに書いてね

		SCENE_NUM,	// シーンの数

		SELECT,	// セレクトシーン
	};

private:
	CScene* pNowScene = nullptr;
	SCENE_NAME nowSceneName;
		
	EffectManeger* effectManeger;
	TextureFactory* textureFactory;
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

	// 現在のシーンを取得
	SCENE_NAME GetNowScene();
};

