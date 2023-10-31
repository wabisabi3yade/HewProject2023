#include "CMizunoScene.h"
#include "CSceneManager.h"
#include"Collision.h"
#include"xa2.h"

CMizunoScene::CMizunoScene()
{
	D3D_CreateSquare({ 3,4 }, &charBuffer);
	D3D_LoadTexture(L"asset/hashimoto/char01.png", &charTexture);

	D3D_CreateSquare({ 1,1 }, &charBuffer2);
	D3D_LoadTexture(L"asset/hashimoto/mizuno.png", &charTexture2);

	charObj = new CObject(charBuffer, charTexture);
	charObj->mTransform.scale = { 3.0f,3.0f,1.0f };

	charObj2 = new CObject(charBuffer2, charTexture2);
	charObj2->mTransform.scale = { 3.0f,3.0f,1.0f };

	charObj2->mTransform.pos = { 5.0f,0.0f,0.0f };

	doToween = new DoTween();

	//HRESULT hr;
	//hr = XA_Initialize();
	//if (FAILED(hr)) // XA_Initialize関数が失敗したか判定
	//{
	//	MessageBoxA(NULL, "サウンド初期化失敗", "エラー", MB_ICONERROR | MB_OK);
	//}

}

CMizunoScene::~CMizunoScene()
{
	XA_Release();

	CLASS_DELETE(charObj);

	SAFE_RELEASE(charBuffer);

	SAFE_RELEASE(charTexture);

	CLASS_DELETE(charObj2);

	SAFE_RELEASE(charBuffer2);

	SAFE_RELEASE(charTexture2);

	CLASS_DELETE(doToween);
}

void CMizunoScene::Update()
{
	input.Update();
	bool coll = CollsionRect(*charObj, *charObj2);
	if (coll)
	{
		doToween->DoMoveX(charObj2, -1.0f, 1.0f,MOVEDIR::LEFT);
	}
	if (gInput->GetKeyTrigger(VK_RIGHT))
	{
		doToween->DoMoveX(charObj, 1.0f, 0.5f,MOVEDIR::RIGHT);
	}
	if (gInput->GetKeyTrigger(VK_LEFT))
	{
		doToween->DoMoveX(charObj, 1.0f, 0.5f,MOVEDIR::LEFT);
	}
	if (gInput->GetKeyTrigger(VK_UP))
	{
		doToween->DoMoveY(charObj, 3.0f, 0.5f, MOVEDIR::UP);
	}
	if (gInput->GetKeyTrigger(VK_DOWN))
	{
		doToween->DoMoveY(charObj, 3.0f, 0.5f, MOVEDIR::DOWN);
	}
	if (input.GetControllerDown(Pad_A))
	{
		doToween->DoMoveX(charObj, 3.0f, 0.1f,MOVEDIR::LEFT);
	}

	if (gInput->GetKeyTrigger(VK_SPACE))
	{
		doToween->DoScaleDown(charObj, 5.0f, 1.0f);
	}
	if (gInput->GetKeyTrigger(VK_RETURN))
	{
		doToween->DoScaleUp(charObj, 5.0f, 1.0f);
	}

	charObj->Update();

	charObj2->Update();
	doToween->Updeta();
}

void CMizunoScene::LateUpdate()
{
}

void CMizunoScene::Draw()
{
	charObj->Draw();
	charObj2->Draw();
}
