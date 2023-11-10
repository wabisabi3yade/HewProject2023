#include "CTatemizoScene.h"
#include "CSceneManager.h"

CTatemizoScene::CTatemizoScene()
{
	D3D_CreateSquare({ 3,4 }, &charBuffer);
	D3D_LoadTexture(L"asset/hashimoto/char01.png", &charTexture);
	charObj = new CObject(charBuffer, charTexture);
	charObj->mTransform.scale = { 3.0f,3.0f,1.0f };
}

CTatemizoScene::~CTatemizoScene()
{
	CLASS_DELETE(charObj);

	CLASS_DELETE(controller);

	SAFE_RELEASE(charBuffer);

	SAFE_RELEASE(charTexture);
}

void CTatemizoScene::Update()
{
	controller -> Update;
}

void CTatemizoScene::LateUpdate()
{
}

void CTatemizoScene::Draw()
{
	charObj->Draw();
}
