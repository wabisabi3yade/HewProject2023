#include "CSceneManager.h"
#include "direct3d.h"
#include "CSelect.h"
#include "CTest.h"
#include "CKawadaScene.h"
#include "CTatemizoScene.h"
#include "CMizunoScene.h"
#include "CWakamuraScene.h"

CSceneManager* CSceneManager::instance = nullptr;

CSceneManager::CSceneManager()
{
	effectManeger = EffectManeger::GetInstance();
}

CSceneManager::~CSceneManager()
{
}

CSceneManager* CSceneManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new CSceneManager();
	}

	return instance;
}

void CSceneManager::Delete()
{
	CLASS_DELETE(instance);
}

void CSceneManager::Act()
{
	// 更新処理 /////////////////////////////////
	// 通常の処理
	pNowScene->Update();
	// 後で行う処理
	pNowScene->LateUpdate();
	
	//エフェクトマネジャー
	effectManeger->Update();
	
	//画面塗りつぶしと設定
	D3D_ClearScreen();
	// 描画処理 /////////////////////////////////
	pNowScene->Draw();

	effectManeger->Draw();
	// 画面更新
	D3D_UpdateScreen();

	pNowScene->SceneChangeCheck();
}



void CSceneManager::SceneChange(int _scene)
{
	// 最初に解放する
	CLASS_DELETE(pNowScene);

	switch (_scene)
	{
	case SELECT:
		nowSceneName = SELECT;
		pNowScene = new CSelect();
		break;

	case KAWADA:
		nowSceneName = KAWADA;
		pNowScene = new CKawadaScene();
		break;

	case TATEMIZO:
		nowSceneName = TATEMIZO;
		pNowScene = new CTatemizoScene();
		break;

	case MIZUNO:
		nowSceneName = MIZUNO;
		pNowScene = new CMizunoScene();
		break;

	case WAKAMURA:
		nowSceneName = WAKAMURA;
		pNowScene = new CWakamuraScene();
		break;

	case HASHIMOTO:
		nowSceneName = HASHIMOTO;
		pNowScene = new CTest();
		break;
	}
}

// シーン番号を返す
CSceneManager::SCENE_NAME CSceneManager::GetNowScene()
{
	return nowSceneName;
}


