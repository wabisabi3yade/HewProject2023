#include "CScene.h"
#include "CSceneManager.h"

CScene::CScene()
{
	// ポインタを取得
	pSceneManager = CSceneManager::GetInstance();
}

CScene::~CScene()
{
}

void CScene::Update()
{
}

// カメラの処理をここに書く
void CScene::LateUpdate()
{
}

void CScene::Draw()
{
}

void CScene::SetScene(int _nextScene)
{
	// シーンを変えるフラグをtrue
	isSceneChange = true;

	// 次に変えるシーンを設定
	nextScene = _nextScene;
}

void CScene::Exit()
{
	isExit = true;
}

void CScene::SceneChangeCheck()
{
	// シーンを変えるフラグがfalseなら処理しない
	if (!isSceneChange) return;

	// シーンを変える関数を呼ぶ
	pSceneManager->SceneChange(nextScene);
}

void CScene::ExitCheck()
{
	if (!isExit) return;

	pSceneManager->Exit();
}
