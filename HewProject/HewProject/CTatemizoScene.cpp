#include "CTatemizoScene.h"

CTatemizoScene::CTatemizoScene()
{
	D3D_CreateSquare({ 3,4 }, &charBuffer);
	D3D_LoadTexture(L"asset/hashimoto/Char01.png", &charTexture);

	charObj = new CObject(charBuffer, charTexture);
	charObj->mTransform.scale = { 3.0f,3.0f,1.0f };
}

CTatemizoScene::~CTatemizoScene()
{
	CLASS_DELETE(charObj);

	SAFE_RELEASE(charBuffer);

	SAFE_RELEASE(charTexture);
}

void CTatemizoScene::Update()
{

    // ベクトルを使って移動
    //charObj->SetMoveSpeed(moveSpeed);
    //pos.x = pos.x + dir.x * moveSpeed;
    //pos.y = pos.y + dir.y * moveSpeed;
    //pos.z = pos.z + dir.z * moveSpeed;
}

void CTatemizoScene::LateUpdate()
{
}

void CTatemizoScene::Draw()
{
	charObj->Draw();
}
