#include "CMizunoScene.h"
#include "CSceneManager.h"
#include"Collision.h"
#include"xa2.h"
#include<vector>


CMizunoScene::CMizunoScene()
{
	D3D_CreateSquare({ 3,4 }, &charBuffer);
	D3D_LoadTexture(L"asset/hashimoto/char01.png", &charTexture);

	D3D_CreateSquare({ 1,1 }, &charBuffer2);
	D3D_LoadTexture(L"asset/hashimoto/mizuno.png", &charTexture2);

	D3D_CreateSquare({ 1,1 }, &fadeBuffer);
	D3D_LoadTexture(L"asset/hashimoto/mizuno.png", &fadeTexture);

	D3D_LoadTexture(L"asset/mizuno/center2.png", &centerTexture);

	stage = new CLoadStage;
	stageMake = new CStageMake;

	std::vector<Stage> StageTable = stage->LoadStage("asset/mizuno/Stage.csv");
	std::vector<STAGEPOS> stagepos = stageMake->StagePos(StageTable);






	charObj = new CObject(charBuffer, charTexture);
	charObj->mTransform.scale = { 3.0f,3.0f,3.0f };

	charObj2 = new CObject(charBuffer2, charTexture2);
	charObj2->mTransform.scale = { 3.0f,3.0f,1.0f };

	charObj2->mTransform.pos = { 5.0f,0.0f,0.0f };

	for (int i = 0; i < 5; i++)
	{
		a[i] = new CObject(charBuffer2, centerTexture);
		a[i]->mTransform.scale = { 0.3f,0.3f,0.3f };
		a[i]->mTransform.pos.z = -1;
	}

	float kariX = 16.0f / 2.0f;
	float kariY = 9.0f / 2.0f;
	int XC = 0;

	for (auto& Stagepos : stagepos)
	{

		//charObj2->mTransform.pos.x = Stagepos.Pos[0]- 8.0f/* - (charObj2->mTransform.scale.x / 2)*/;

		//ステージの配置関連
		if (XC == 0)
		{
			charObj->mTransform.pos.x = Stagepos.Pos[0] - kariX /** CCamera::scaleScreen*/ + (charObj->mTransform.scale.x / 2);
			charObj->mTransform.pos.y = (Stagepos.Pos[1] * -1.0f) + kariY /** CCamera::scaleScreen*/ - (charObj->mTransform.scale.y / 2);
		}
		XC++;
	}
	//charObj->mTransform.pos.y = +4.5f;
	//Stagepos.Pos[0];

	fade = new CFade(charBuffer2, charTexture2);
	fade->mTransform.pos = Vector3::zero;
	fade->mTransform.scale = { 5.0f,5.0f,1.0f };

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

	CLASS_DELETE(fade);

	SAFE_RELEASE(fadeBuffer);
	SAFE_RELEASE(fadeTexture);

	CLASS_DELETE(stageMake);
	CLASS_DELETE(stage);

	CLASS_DELETE(a[0]);
	CLASS_DELETE(a[1]);
	CLASS_DELETE(a[2]);
	CLASS_DELETE(a[3]);
	CLASS_DELETE(a[4]);
	SAFE_RELEASE(centerTexture);

	CLASS_DELETE(doToween);
}

void CMizunoScene::Update()
{
	input.Update();
	//bool coll = CollsionRect(*charObj, *charObj2);
	//if (coll)
	//{
	//	doToween->DoMoveX(charObj2, -1.0f, 1.0f,MOVEDIR::LEFT);
	//}
	if (gInput->GetKeyTrigger(VK_RIGHT))
	{
		doToween->DoMoveX(charObj, 1.0f, 0.5f, MOVEDIR::RIGHT);
		//charObj->mTransform.pos.x += 1;
	}
	if (gInput->GetKeyTrigger(VK_LEFT))
	{
		doToween->DoMoveX(charObj, 1.0f, 0.5f, MOVEDIR::LEFT);
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
		doToween->DoMoveX(charObj, 3.0f, 0.1f, MOVEDIR::LEFT);
	}

	if (gInput->GetKeyTrigger(VK_SPACE))
	{
		//doToween->DoScaleDown(charObj, 5.0f, 1.0f);
		fade->FadeOut(fade->RIGHT, 1);
	}
	if (gInput->GetKeyTrigger(VK_RETURN))
	{
		//doToween->DoScaleUp(charObj, 5.0f, 1.0f);
		//Vector3 kari = { 4,0,0 };
		//doToween->DoMoveCurve(charObj, kari, 3.5f, 0.2f);

		//doToween->DoMove(charObj, 1.0f, 1.0f, MOVEDIR::TO_TOP_LEFT);
		fade->FadeIn(fade->TO_TOP_RIGHT, 1);
	}
	doToween->Update();
	charObj->Update();
	Vector3 x(charObj->mTransform.pos.x, charObj->mTransform.pos.y, charObj->mTransform.pos.z);
	a[0]->mTransform.pos.x = x.x; // charObj2->mTransform.pos;
	a[0]->mTransform.pos.y = x.y; // charObj2->mTransform.pos;

	a[1]->mTransform.pos.x = x.x - charObj->mTransform.scale.x/2;
	a[1]->mTransform.pos.y = x.y + charObj->mTransform.scale.y/2;

	a[2]->mTransform.pos.x = x.x + charObj->mTransform.scale.x / 2;
	a[2]->mTransform.pos.y = x.y + charObj->mTransform.scale.y / 2;

	a[3]->mTransform.pos.x = x.x + charObj->mTransform.scale.x / 2;
	a[3]->mTransform.pos.y = x.y - charObj->mTransform.scale.y / 2;

	a[4]->mTransform.pos.x = x.x - charObj->mTransform.scale.x / 2;
	a[4]->mTransform.pos.y = x.y - charObj->mTransform.scale.y / 2;

	//a->mTransform.pos.z = x.z; // charObj2->mTransform.pos;
	charObj2->Update();
	a[0]->Update();
	a[1]->Update();
	a[2]->Update();
	a[3]->Update();
	a[4]->Update();
	fade->Update();

}

void CMizunoScene::LateUpdate()
{
}

void CMizunoScene::Draw()
{
	charObj->Draw();
	charObj2->Draw();
	a[0]->Draw();
	a[1]->Draw();
	a[2]->Draw();
	a[3]->Draw();
	a[4]->Draw();
	fade->Draw();
}
