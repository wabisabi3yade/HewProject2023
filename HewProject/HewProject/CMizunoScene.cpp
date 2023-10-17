#include "CMizunoScene.h"
#include "CSceneManager.h"

CMizunoScene::CMizunoScene()
{
	D3D_CreateSquare({ 3,4 }, &charBuffer);
	D3D_LoadTexture(L"asset/hashimoto/char01.png", &charTexture);

	charObj = new CObject(charBuffer, charTexture);
	charObj->mTransform.scale = { 3.0f,3.0f,1.0f };
	doToween = new DoTween();
}

CMizunoScene::~CMizunoScene()
{
	CLASS_DELETE(charObj);

	SAFE_RELEASE(charBuffer);

	SAFE_RELEASE(charTexture);
}

void CMizunoScene::Update()
{
	if (gInput->GetKeyTrigger(VK_RIGHT))
	{
		doToween->DoMoveX(charObj, 1.0f, 0.5f);
	}
	charObj->Update();
	doToween->Updeta();
}

void CMizunoScene::LateUpdate()
{
}

void CMizunoScene::Draw()
{
	charObj->Draw();
}
