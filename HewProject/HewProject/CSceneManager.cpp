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
#include "CMenu.h"
#include "CGameStart.h"
#include "LoadingScene.h"

CSceneManager* CSceneManager::instance = nullptr;

CSceneManager::CSceneManager()
{
	//�T�E���h������
	HRESULT hr;
	hr = XA_Initialize();

	//XA_Initialize�֐����s����������
	if (FAILED(hr))
	{
		MessageBoxA(NULL, "�T�E���h���������s", "�G���[", MB_ICONERROR | MB_OK);
	}

	effectManeger = EffectManeger::GetInstance();
	textureFactory = TextureFactory::GetInstance();
	inputManager = InputManager::GetInstance();
	fade = Fade::GetInstance();

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
	//�T�E���h�������
	XA_Release();
	CLASS_DELETE(instance);
}

void CSceneManager::Act()
{
	// �X�V���� /////////////////////////////////

	// ���͂̏�ԍX�V
	inputManager->Update();

	// �ʏ�̏���
	pNowScene->Update();
	// ��ōs������
	pNowScene->LateUpdate();

	//�G�t�F�N�g�}�l�W���[
	effectManeger->Update();

	// �t�F�[�h�̍X�V����
	fade->Update();

	//��ʓh��Ԃ��Ɛݒ�
	D3D_ClearScreen();
	// �`�揈�� /////////////////////////////////
	pNowScene->Draw();

	effectManeger->Draw();

	// �t�F�[�h�`��
	// 1�Ԍ�ɏ���
	fade->Draw();

	// ��ʍX�V
	D3D_UpdateScreen();

	pNowScene->SceneChangeCheck();

	// �t�F�[�h���V�[���`�F���W�����Ă邩�ǂ����m�F
	FadeSceneChangeCheck();
	
	pNowScene->ExitCheck();
}


void CSceneManager::SceneChange(int _scene)
{
	// �ŏ��ɉ������
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

	case CScene::WORLD1_SELECT:
		nowSceneName = CScene::WORLD1_SELECT;
		pNowScene = new W1Select();
		break;

	case CScene::WORLD2_SELECT:
		nowSceneName = CScene::WORLD2_SELECT;
		pNowScene = new W2Select();
		break;

	case CScene::MENU:
		nowSceneName = CScene::MENU;
		pNowScene = new CMenu();
		break;

	case CScene::GAMESTART:
		nowSceneName = CScene::GAMESTART;
		pNowScene = new CGameStart();
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
	// �ŏ��ɉ������
	CLASS_DELETE(pNowScene);
	XA_Stop(SOUND_LABEL_BGMSWEETSFACTORY);

	pNowScene = new Stage(_path);
}

void CSceneManager::Exit()
{
	isGameExit = true;
}

// �V�[���ԍ���Ԃ�
CScene::SCENE_NAME CSceneManager::GetNowScene()
{
	return nowSceneName;
}

void CSceneManager::FadeSceneChangeCheck()
{
	if (!fade->GetLoadChange()) return;

	// ���[�h�Ɉڍs
	SceneChange(CScene::SCENE_NAME::LOADING);
}


