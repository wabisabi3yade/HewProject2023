#include "CSceneManager.h"
#include "direct3d.h"
#include "CSelect.h"
#include "CTest.h"
#include "CKawadaScene.h"
#include "CTatemizoScene.h"
#include "CMizunoScene.h"
#include "CWakamuraScene.h"
#include "Stage.h"
#include "CCamera.h"
#include "CWorldSelectScene.h"
#include "CStage1SelectScene.h"
CSceneManager* CSceneManager::instance = nullptr;

CSceneManager::CSceneManager()
{
	effectManeger = EffectManeger::GetInstance();
	textureFactory = TextureFactory::GetInstance();
}

CSceneManager::~CSceneManager()
{
	CLASS_DELETE(pNowScene);

	EffectManeger::Delete();
	CCamera::Delete();
	TextureFactory::Delete();
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
	case CScene::SELECT:
		nowSceneName = CScene::SELECT;
		pNowScene = new CSelect();
		break;

	case CScene::KAWADA:
		nowSceneName = CScene::KAWADA;
		pNowScene = new CKawadaScene();
		break;

	case CScene::TATEMIZO:
		nowSceneName = CScene::TATEMIZO;
		pNowScene = new CTatemizoScene();
		break;

	case CScene::MIZUNO:
		nowSceneName = CScene::MIZUNO;
		pNowScene = new CMizunoScene();
		break;

	case CScene::WAKAMURA:
		nowSceneName = CScene::WAKAMURA;
		pNowScene = new CWorldSelectScene();
		break;

	case CScene::HASHIMOTO:
		nowSceneName = CScene::HASHIMOTO;
		pNowScene = new Stage(L"asset/mizuno/Stage.csv");
		break;
	case CScene::STAGE1:
		nowSceneName = CScene::STAGE1;
		pNowScene = new CStage1SelectScene();
		break;
	}
}

// シーン番号を返す
CScene::SCENE_NAME CSceneManager::GetNowScene()
{
	return nowSceneName;
}


