#include "CTatemizoScene.h"
#include "CSceneManager.h"

CTatemizoScene::CTatemizoScene() : player(nullptr)
{
	// CPlayer オブジェクトの初期化
	//player = new CPlayer(0.0f, 0.0f, 1.0f);
}

CTatemizoScene::~CTatemizoScene()
{
	// CPlayer オブジェクトの解放
	delete player;
	player = nullptr;
}

void CTatemizoScene::Update()
{
	// CPlayer の Update 関数を呼び出す
	player->Update();
}

void CTatemizoScene::LateUpdate()
{
}

void CTatemizoScene::Draw()
{
}
