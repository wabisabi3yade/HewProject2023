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
#include "W1Select.h"
#include "W2Select.h"
#include "W3Select.h"
#include "W4Select.h"
#include "CMenu.h"
#include "CGameStart.h"
#include "LoadingScene.h"

// ステージのインクルード
#include "Stage11.h"
#include "Stage12.h"
#include "Stage13.h"
#include "Stage14.h"
#include "Stage15.h"
#include "Stage16.h"
#include "Stage21.h"
#include "Stage22.h"
#include "Stage23.h"
#include "Stage24.h"
#include "Stage31.h"
#include "Stage32.h"
#include "Stage33.h"
#include "Stage34.h"
#include "StageEx1.h"
#include "StageEx2.h"
#include "StageEx3.h"
#include "StageEx4.h"




CSceneManager* CSceneManager::instance = nullptr;

CSceneManager::CSceneManager()
{
	//サウンド初期化
	HRESULT hr;
	hr = XA_Initialize();

	//XA_Initialize関数失敗したか判定
	if (FAILED(hr))
	{
		MessageBoxA(NULL, "サウンド初期化失敗", "エラー", MB_ICONERROR | MB_OK);
	}

	effectManeger = EffectManeger::GetInstance();
	textureFactory = TextureFactory::GetInstance();
	inputManager = InputManager::GetInstance();
	fade = Fade::GetInstance();

}

CSceneManager::~CSceneManager()
{
	SetPlayBgm(SOUND_LABEL::NONE);

	CLASS_DELETE(pNowScene);

	EffectManeger::Delete();
	CCamera::Delete();
	TextureFactory::Delete();
	Fade::Delete();
	InputManager::Delete();
}

void CSceneManager::OnEscape()
{
	if (gInput->GetKeyTrigger(VK_ESCAPE))
	{
		Exit();
	}
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
	//サウンド解放処理
	XA_Release();
}

void CSceneManager::Act()
{
	// 更新処理 /////////////////////////////////

	// 入力の状態更新
	inputManager->Update();

	// Escapeキー入力されているか
	OnEscape();

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

	SceneChangeCheck();
	// フェードがシーンチェンジさせてるかどうか確認
	LoadSceneChangeCheck();
}


void CSceneManager::SceneChange(int _scene)
{
	// 最初に解放する
	CLASS_DELETE(pNowScene);
	// 変える先のシーン名を保存
	nowSceneName = static_cast<CScene::SCENE_NAME>(_scene);

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
		/*pNowScene = new Stage(L"Test.csv", 1);*/
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
		pNowScene = new CGameClear(CScene::SCENE_NAME::NONE);
		break;

	case CScene::WORLD1_SELECT:
		nowSceneName = CScene::WORLD1_SELECT;
		pNowScene = new W1Select();
		break;

	case CScene::WORLD2_SELECT:
		nowSceneName = CScene::WORLD2_SELECT;
		pNowScene = new W2Select();
		break;

	case CScene::WORLD3_SELECT:
		nowSceneName = CScene::WORLD3_SELECT;
		pNowScene = new W3Select();
		break;

	case CScene::WORLD4_SELECT:
		nowSceneName = CScene::WORLD4_SELECT;
		pNowScene = new W4Select();
		break;

	case CScene::STAGE1_1:
		pNowScene = new Stage11();
		break;

	case CScene::STAGE1_2:
		pNowScene = new Stage12();
		break;

	case CScene::STAGE1_3:
		pNowScene = new Stage13();
		break;

	case CScene::STAGE1_4:
		pNowScene = new Stage14();
		break;

	case CScene::STAGE1_5:
		pNowScene = new Stage15();
		break;

	case CScene::STAGE1_6:
		pNowScene = new Stage16();
		break;

	case CScene::STAGE2_1:
		pNowScene = new Stage21();
		break;

	case CScene::STAGE2_2:
		pNowScene = new Stage22();
		break;

	case CScene::STAGE2_3:
		pNowScene = new Stage23();
		break;

	case CScene::STAGE2_4:
		pNowScene = new Stage24();
		break;

	case CScene::STAGE3_1:
		pNowScene = new Stage31();
		break;

	case CScene::STAGE3_2:
		pNowScene = new Stage32();
		break;

	case CScene::STAGE3_3:
		pNowScene = new Stage33();
		break;

	case CScene::STAGE3_4:
		pNowScene = new Stage34();
		break;

	case CScene::STAGE4_1:
		pNowScene = new StageEx1();
		break;

	case CScene::STAGE4_2:
		pNowScene = new StageEx2();
		break;

	case CScene::STAGE4_3:
		pNowScene = new StageEx3();
		break;

	case CScene::STAGE4_4:
		pNowScene = new StageEx4();
		break;

	case CScene::MENU:
		nowSceneName = CScene::MENU;
		pNowScene = new CMenu();
		break;

	case CScene::GAMESTART:
		/*nowSceneName = CScene::GAMESTART;
		pNowScene = new CGameStart();*/
		break;

	case CScene::SCENE_NAME::LOADING:
		nowSceneName = CScene::LOADING;
		pNowScene = new LoadingScene();
		break;

		/*case CScene::HOSODA_SELECT:
			nowSceneName = CScene::HOSODA_SELECT;
			pNowScene = new HosodaSelect();
			break;*/
	}
}

void CSceneManager::SceneChangeStage(const wchar_t* _path)
{
	//// 最初に解放する
	//CLASS_DELETE(pNowScene);


	//pNowScene = new Stage(_path, 1);
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

void CSceneManager::SceneChangeCheck()
{
	if (!fade->GetIsChange()) return;

	// ロードに移行
	SceneChange(fade->GetNextScene());
}

void CSceneManager::LoadSceneChangeCheck()
{
	if (!fade->GetLoadChange()) return;

	// ロードに移行
	SceneChange(CScene::SCENE_NAME::LOADING);
}

void CSceneManager::SetPlayBgm(int _setBgm)
{
	// 同じ曲なら
	if (playingBgm == _setBgm) return;

	// 何も設定していないときは
	if (playingBgm != SOUND_LABEL::NONE)
	{
		XA_Stop(static_cast<SOUND_LABEL>(playingBgm));
		playingBgm = SOUND_LABEL::NONE;
	}

	// 何も設定しないなら
	if (_setBgm != SOUND_LABEL::NONE)
	{
		XA_Play(static_cast<SOUND_LABEL>(_setBgm));
		playingBgm = _setBgm;
	}

}


