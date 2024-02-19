#include "CScene.h"
#include "CSceneManager.h"

CScene::CScene()
{
	// �|�C���^���擾
	pSceneManager = CSceneManager::GetInstance();
}

CScene::~CScene()
{
}

void CScene::Update()
{
}

// �J�����̏����������ɏ���
void CScene::LateUpdate()
{
}

void CScene::Draw()
{
}

void CScene::SetScene(int _nextScene)
{
	// �V�[����ς���t���O��true
	isSceneChange = true;

	// ���ɕς���V�[����ݒ�
	nextScene = _nextScene;
}

void CScene::Exit()
{
	isExit = true;
}

void CScene::SceneChangeCheck()
{
	// �V�[����ς���t���O��false�Ȃ珈�����Ȃ�
	if (!isSceneChange) return;

	// �V�[����ς���֐����Ă�
	pSceneManager->SceneChange(nextScene);
}

void CScene::ExitCheck()
{
	if (!isExit) return;

	pSceneManager->Exit();
}
