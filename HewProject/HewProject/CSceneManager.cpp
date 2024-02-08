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
#include "Fade_TestScene.h"
#include "xa2.h"
#include "CTitleScene.h"
#include "HosodaSelect.h"
#include "CGameOver.h"
#include "CGameClear.h"

CSceneManager* CSceneManager::instance = nullptr;

CSceneManager::CSceneManager()
{
	effectManeger = EffectManeger::GetInstance();
	textureFactory = TextureFactory::GetInstance();
	inputManager = InputManager::GetInstance();
	fade = Fade::GetInstance();

	//サウンド初期化
	HRESULT hr;
	hr = XA_Initialize();

	//XA_Initialize関数失敗したか判定
	if (FAILED(hr))
	{
		MessageBoxA(NULL, "サウンド初期化失敗", "エラー", MB_ICONERROR | MB_OK);
	}

	XA_Play(SOUND_LABEL_BGMSWEETSFACTORY);
}

CSceneManager::~CSceneManager()
{
	CLASS_DELETE(pNowScene);

	EffectManeger::Delete();
	CCamera::Delete();
	TextureFactory::Delete();
	Fade::Delete();
	InputManager::Delete();
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
	//サウンド解放処理
	XA_Release();
	CLASS_DELETE(instance);
}

void CSceneManager::Act()
{
	// 更新処理 /////////////////////////////////
	
	// 入力の状態更新
	inputManager->Update();

	// 通常の処理
	pNowScene->Update();
	// 後で行う処理
	pNowScene->LateUpdate();
	
	//エフェクトマネジャー
	effectManeger->Update();

	// フェードの更新処理
	fade->Update();
	
	//画面塗りつぶしと設定
	D3D_ClearScreen();
	// 描画処理 /////////////////////////////////
	pNowScene->Draw();

	effectManeger->Draw();

	// フェード描画
	// 1番後に書く
	fade->Draw();

	// 画面更新
	D3D_UpdateScreen();

	pNowScene->SceneChangeCheck();
	pNowScene->ExitCheck();
}



void CSceneManager::SceneChange(int _scene)
{
	// 最初に解放する
	CLASS_DELETE(pNowScene);
	XA_Stop(SOUND_LABEL_BGMSWEETSFACTORY);

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
		XA_Play(SOUND_LABEL_BGMSWEETSFACTORY);
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

	case CScene::FADE_TEST:
		nowSceneName = CScene::FADE_TEST;
		pNowScene = new Fade_TestScene();
		break;

	case CScene::TITLE:
		nowSceneName = CScene::TITLE;
		pNowScene = new CTitleScene();
		break;

	case CScene::GAMEOVER:
		nowSceneName = CScene::GAMEOVER;
		pNowScene = new CGameOver();
		break;

	case CScene::GAMECLEAR:
		nowSceneName = CScene::GAMECLEAR;
		pNowScene = new CGameClear();
		break;

	/*case CScene::HOSODA_SELECT:
		nowSceneName = CScene::HOSODA_SELECT;
		pNowScene = new HosodaSelect();
		break;*/
	}
}

void CSceneManager::SceneChangeStage(const wchar_t* _path)
{
	// 最初に解放する
	CLASS_DELETE(pNowScene);
	XA_Stop(SOUND_LABEL_BGMSWEETSFACTORY);

	pNowScene = new Stage(_path);
}

void CSceneManager::Exit()
{
	isGameExit = true;
}

// シーン番号を返す
CScene::SCENE_NAME CSceneManager::GetNowScene()
{
	return nowSceneName;
}


