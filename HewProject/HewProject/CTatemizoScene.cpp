#include "CTatemizoScene.h"
#include "CSceneManager.h"

CTatemizoScene::CTatemizoScene() : player(nullptr)
{
	// CPlayer �I�u�W�F�N�g�̏�����
	//player = new CPlayer(0.0f, 0.0f, 1.0f);
}

CTatemizoScene::~CTatemizoScene()
{
	// CPlayer �I�u�W�F�N�g�̉��
	delete player;
	player = nullptr;
}

void CTatemizoScene::Update()
{
	// CPlayer �� Update �֐����Ăяo��
	player->Update();
}

void CTatemizoScene::LateUpdate()
{
}

void CTatemizoScene::Draw()
{
}
