#include "CTatemizoScene.h"
#include "CSceneManager.h"

CTatemizoScene::CTatemizoScene() : player(nullptr)
{
	D3D_CreateSquare({ 3,4 }, &charBuffer);
	D3D_LoadTexture(L"asset/hashimoto/char01.png", &charTexture);

	//charObj = new CObject(charBuffer, charTexture);
	//charObj->mTransform.scale = { 3.0f,3.0f,1.0f };

	// CPlayer �I�u�W�F�N�g�̏�����
	player = new CPlayer(charBuffer, charTexture);
}

CTatemizoScene::~CTatemizoScene()
{
	CLASS_DELETE(charObj);

	SAFE_RELEASE(charBuffer);

	SAFE_RELEASE(charTexture);

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
	player->Draw();
}
