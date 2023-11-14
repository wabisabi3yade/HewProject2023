#include "CTatemizoScene.h"
#include "CSceneManager.h"

CTatemizoScene::CTatemizoScene() : player(nullptr)
{
	D3D_CreateSquare({ 3,4 }, &charBuffer);
	D3D_LoadTexture(L"asset/hashimoto/char01.png", &charTexture);

	//charObj = new CObject(charBuffer, charTexture);
	//charObj->mTransform.scale = { 3.0f,3.0f,1.0f };

	// CPlayer オブジェクトの初期化
	player = new CPlayer(charBuffer, charTexture);
}

CTatemizoScene::~CTatemizoScene()
{
	CLASS_DELETE(charObj);

	SAFE_RELEASE(charBuffer);

	SAFE_RELEASE(charTexture);

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
	player->Draw();
}
