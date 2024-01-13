#include <DirectXMath.h>
#include "direct3d.h"
#include "CTatemizoScene.h"
#include "CInput.h"
#include "COperation.h"


CTatemizoScene::CTatemizoScene()
{
	D3D_CreateSquare({ 3,4 }, &charBuffer);
	D3D_LoadTexture(L"asset/hashimoto/Char01.png", &charTexture);

	charObj = new CObject(charBuffer, charTexture);
	charObj->mTransform.scale = { 3.0f,3.0f,1.0f };

	x = new GameController();

}

CTatemizoScene::~CTatemizoScene()
{
	CLASS_DELETE(charObj);

	SAFE_RELEASE(charBuffer);

	SAFE_RELEASE(charTexture);

	CLASS_DELETE(x)
}

void CTatemizoScene::Update()
{

	Vector3 G (x->GamePad());
	
	charObj->mTransform.pos.x += G.x*0.01;
	charObj->mTransform.pos.y += G.y*0.01;

}

void CTatemizoScene::LateUpdate()
{
}

void CTatemizoScene::Draw()
{
	charObj->Draw();
}
