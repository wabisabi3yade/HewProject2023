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
	// �X�V���� /////////////////////////////////
	// �ʏ�̏���
	pNowScene->Update();
	// ��ōs������
	pNowScene->LateUpdate();
	
	//�G�t�F�N�g�}�l�W���[
	effectManeger->Update();
	
	//��ʓh��Ԃ��Ɛݒ�
	D3D_ClearScreen();
	// �`�揈�� /////////////////////////////////
	pNowScene->Draw();

	effectManeger->Draw();
	// ��ʍX�V
	D3D_UpdateScreen();

	pNowScene->SceneChangeCheck();
}



void CSceneManager::SceneChange(int _scene)
{
	// �ŏ��ɉ������
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

// �V�[���ԍ���Ԃ�
CSceneManager::SCENE_NAME CSceneManager::GetNowScene()
{
	return nowSceneName;
}


