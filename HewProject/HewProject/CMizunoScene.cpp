#include "CMizunoScene.h"
#include "CSceneManager.h"
#include"Collision.h"
#include"xa2.h"
#include<vector>
#include"Time.h"
#include<iostream>
#include<algorithm>
#include"StageScene.h"

#define stageChack (4)
float fixedCount = 0;	//fps固定用変数
void Z_Sort(std::vector<CObject*>& _sortList)
{

	std::sort(_sortList.begin(), _sortList.end(), [](CObject* a, CObject* b) {return (a->mTransform.pos.z > b->mTransform.pos.z); });
}

CMizunoScene::CMizunoScene()
{
	D3D_CreateSquare({ 3,4 }, &charBuffer);
	D3D_LoadTexture(L"asset/mizuno/floor_g.png", &charTexture);

	D3D_CreateSquare({ 1,1 }, &charBuffer2);
	D3D_LoadTexture(L"asset/hashimoto/mizuno.png", &charTexture2);

	D3D_CreateSquare({ 1,1 }, &fadeBuffer);
	D3D_LoadTexture(L"asset/mizuno/floor_y (1).png", &fadeTexture);

	D3D_LoadTexture(L"asset/mizuno/center2.png", &centerTexture);

	//stage = new CLoadStage;
	//stageMake = new CStageMake;

	//std::vector<LoadData> StageData = stage->LoadStage(L"asset/mizuno/Stage.csv");
	//std::vector<STAGEPOS> stagepos = stageMake->StagePos(StageData, 13);

	stagescene = new StageScene(NULL,NULL);
	stagescene->Init();
	//std::vector<Stage> StageTable = stage->LoadStage("asset/mizuno/Stage.csv");
	//std::vector<STAGEPOS> stagepos = stageMake->StagePos(StageTable);


	//for (int i = 0; i < stagepos.size(); i++)
	//{
	//	if (i % 2 == 0)
	//	{
	//		stageobj[i] = new CObject(charBuffer2, charTexture);
	//	}
	//	else
	//	{
	//		stageobj[i] = new CObject(charBuffer2, fadeTexture);
	//	}
	//	stageobj[i]->mTransform.scale = { 1.0f,1.0f,1.0f };
	//}




	charObj = new CObject(charBuffer2, charTexture);
	charObj->mTransform.scale = { 3.0f,3.0f,3.0f };

	charObj2 = new CObject(charBuffer2, charTexture);
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
	int nStage = 0;

	//for (auto& Stagepos : stagepos)
	//{

	//	//charObj2->mTransform.pos.x = Stagepos.Pos[0]- 8.0f/* - (charObj2->mTransform.scale.x / 2)*/;

	//	//ステージの配置関連
	//	if (nStage == 0)
	//	{
	//		charObj->mTransform.pos.x = Stagepos.pos.x - kariX + (charObj->mTransform.scale.x / 2);
	//		charObj->mTransform.pos.y = (Stagepos.pos.y * -1.0f) + kariY - (charObj->mTransform.scale.y / 2);
	//	}
	//	if (nStage == 13)
	//	{
	//		charObj2->mTransform.pos.x = Stagepos.pos.x - kariX + (charObj2->mTransform.scale.x / 2);
	//		charObj2->mTransform.pos.y = (Stagepos.pos.y * -1.0f) + kariY - (charObj2->mTransform.scale.y / ((charObj2->mTransform.scale.y / 2) - 0.1f));

	//	}

	//	// stageposから何行目かを見ないと分からない　13*3のモノから0が入っているもの分引いてあるから

	//	if (nStage % 2 == 0)
	//	{
	//		stageobj[nStage] = new CObject(charBuffer2, charTexture);
	//	}
	//	else
	//	{
	//		stageobj[nStage] = new CObject(charBuffer2, fadeTexture);
	//	}
	//	stageobj[nStage]->mTransform.scale = { 2.0f,2.0f,2.0f };

	//	int kari = (int)Stagepos.pos.x;

	///*		if (Stagepos.blockType == 1)
	//		{
	//			stageobj[XC]->SetTexture(fadeTexture);
	//		}
	//		if (Stagepos.blockType == 2)
	//		{
	//			stageobj[XC]->SetTexture(charTexture2);
	//		}*/

	//	//if ((kari % 13) == 0)
	//	//{
	//	//	stageobj[nStage]->mTransform.pos.x = -kariX + (stageobj[nStage]->mTransform.scale.x / 2) + (stageobj[nStage]->mTransform.scale.x / 2 * Stagepos.pos.y);
	//	//	stageobj[nStage]->mTransform.pos.y = (stageobj[nStage]->mTransform.scale.y * Stagepos.pos.y * -1.0f)  + (0.03f * (Stagepos.pos.x + Stagepos.pos.y) * stageobj[nStage]->mTransform.scale.y) - (stageobj[nStage]->mTransform.scale.y / 2) + (stageobj[nStage]->mTransform.scale.y / 2 * Stagepos.pos.y) - ((stageobj[nStage]->mTransform.scale.y / 2) * (Stagepos.pos.y)) + ((stageobj[nStage]->mTransform.scale.y / 2) * (Stagepos.pos.y)) + ((stageobj[nStage]->mTransform.scale.y / 4) * (Stagepos.pos.y + 1)) -(0.1f * Stagepos.pos.y)/*+0.3f*/;
	//	//	if (stageobj[nStage]->mTransform.pos.y < 0)
	//	//	{
	//	//		stageobj[nStage]->mTransform.pos.z = stageobj[nStage]->mTransform.pos.y * 0.01f;
	//	//	}
	//	//	else
	//	//	{
	//	//		stageobj[nStage]->mTransform.pos.z = stageobj[nStage]->mTransform.pos.y * 0.01f;
	//	//	}
	//	//}
	//	//else
	//	//{
	//	//	stageobj[nStage]->mTransform.pos.x = -kariX + (stageobj[nStage]->mTransform.scale.x / 2) + ((stageobj[nStage]->mTransform.scale.x / 2) * (int)(kari + Stagepos.pos.y))-0.01f*Stagepos.pos.x;
	//	//	stageobj[nStage]->mTransform.pos.y = (stageobj[nStage]->mTransform.scale.y * Stagepos.pos.y * -1.0f) + (0.03f * (Stagepos.pos.x + Stagepos.pos.y)*stageobj[nStage]->mTransform.scale.y) - (stageobj[nStage]->mTransform.scale.y / 2) + (stageobj[nStage]->mTransform.scale.y / 2 * Stagepos.pos.y) - ((stageobj[nStage]->mTransform.scale.y / 2) * (Stagepos.pos.y)) + ((stageobj[nStage]->mTransform.scale.y / 2) * (Stagepos.pos.y)) + ((stageobj[nStage]->mTransform.scale.y / 4) * (Stagepos.pos.y + 1)) + ((stageobj[nStage]->mTransform.scale.y / 4) * (Stagepos.pos.x)) - (0.1f * Stagepos.pos.y) /*+0.01f*Stagepos.pos.x*/;
	//	//	if (stageobj[nStage]->mTransform.pos.y < 0)
	//	//	{
	//	//		stageobj[nStage]->mTransform.pos.z = +stageobj[nStage]->mTransform.pos.y * 0.01f;
	//	//	}
	//	//	else
	//	//	{
	//	//		stageobj[nStage]->mTransform.pos.z = +stageobj[nStage]->mTransform.pos.y * 0.01f;
	//	//	}
	//	//}

	//	//
	//	//
	//	//if (kari % 13 == 0)
	//	//{
	//	//	if (kari/13 == 0)
	//	//	{
	//	//		stageobj[XC]->mTransform.pos.x = Stagepos.Pos[0] - kariX + (stageobj[XC]->mTransform.scale.x / 2);
	//	//		stageobj[XC]->mTransform.pos.y = (Stagepos.Pos[1] * -1.0f) + 0.1f - (stageobj[XC]->mTransform.scale.y / 2);
	//	//		stageobj[XC]->mTransform.pos.z = -0.5f;
	//	//	}
	//	//	else
	//	//	{
	//	//		stageobj[XC]->mTransform.pos.x = Stagepos.Pos[0] - kariX + (stageobj[XC]->mTransform.scale.x / 2) + (stageobj[XC]->mTransform.scale.x / 2) + ((stageobj[XC]->mTransform.scale.x / 2)*(Stagepos.Pos[1]));
	//	//		//stageobj[XC]->mTransform.pos.y = (Stagepos.Pos[1] * -1.0f) + 0.1f * XC  - (stageobj[XC]->mTransform.scale.y / 2 ) - stageobj[XC]->mTransform.scale.y / 3 - 0.2f;
	//	//		stageobj[XC]->mTransform.pos.y = /*(Stagepos.Pos[1] * -1.0f)*/ + 0.1f - (stageobj[XC]->mTransform.scale.y / 2) - ((stageobj[XC]->mTransform.scale.y ) * (Stagepos.Pos[1]));
	//	//		stageobj[XC]->mTransform.pos.z = -0.5f + (0.01f * XC );
	//	//	}
	//	//}
	//	//else
	//	//{
	//	//	stageobj[XC]->mTransform.pos.x = -kariX + (stageobj[XC]->mTransform.scale.x / 2) + ((stageobj[XC]->mTransform.scale.x /2) * (int)(kari%13));
	//	//	stageobj[XC]->mTransform.pos.y = (Stagepos.Pos[1] * -1.0f) - (stageobj[XC]->mTransform.scale.y / 2) + ((stageobj[XC]->mTransform.scale.y / 2) * (Stagepos.Pos[1]) - (stageobj[XC]->mTransform.scale.y /2 * (Stagepos.Pos[1]))) + 0.1f;
	//	//	//stageobj[XC]->mTransform.pos.y = -(stageobj[XC]->mTransform.scale.y / 2) + ((stageobj[XC]->mTransform.scale.y / 2) * (int)(XC / 13)) + 0.1f;
	//	//
	//	//	
	//	//	/*if (XC == 1)
	//	//	if(XC ==2)
	//	//	stageobj[XC]->mTransform.pos.z =  -0.3f;
	//	//	*/
	//	//	stageobj[XC]->mTransform.pos.z = -0.5f + (0.01f * XC);
	//	//}
	//	//stageObj.push_back(stageobj[nStage]);
	//	//nStage++;

	//}
	//stageObj[14]->mTransform.pos.y -= stageObj[14]->mTransform.scale.y / 2;
	//stageObj[14]->mTransform.pos.x += stageObj[14]->mTransform.scale.x / 2;
	//std::sort(stageObj.begin(), stageObj.end(), [](CObject* a, CObject* b) {return (a->mTransform.pos.z > b->mTransform.pos.z); });

	//Z_Sort(stageObj);

	//charObj->mTransform.pos.y = +4.5f;
	//Stagepos.Pos[0];
	//stageobj[14]->mTransform.pos.x = stageobj[13]->mTransform.pos.x + stageobj[14]->mTransform.scale.x/2;
	//stageobj[14]->mTransform.pos.y = stageobj[13]->mTransform.pos.y + stageobj[14]->mTransform.scale.y / 4 +0.1f;



	fade = new CFade(charBuffer2, charTexture2);
	fade->mTransform.pos = Vector3::zero;
	fade->mTransform.scale = { 5.0f,5.0f,1.0f };

	//doToween = new DoTween();

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

	//CLASS_DELETE(stageMake);
	//CLASS_DELETE(stage);

	CLASS_DELETE(a[0]);
	CLASS_DELETE(a[1]);
	CLASS_DELETE(a[2]);
	CLASS_DELETE(a[3]);
	CLASS_DELETE(a[4]);

	//for (int i = 0; i < 39; i++)
	//{
	//	CLASS_DELETE(stageobj[i])
	//}
	SAFE_RELEASE(centerTexture);

	CLASS_DELETE(stagescene);
	//CLASS_DELETE(doToween);
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
		//doToween->DoMoveX(charObj, 1.0f, 0.5f, MOVEDIR::RIGHT);
		//charObj->mTransform.pos.x += 1;
		
		//if (ss < 38)
		//	ss++;
	}
	if (gInput->GetKeyTrigger(VK_LEFT))
	{
		//doToween->DoMoveX(charObj, 1.0f, 0.5f, MOVEDIR::LEFT);
		//Time::isSlow = true;

		//if (ss > 0)
		//	ss--;
	}
	if (gInput->GetKeyTrigger(VK_UP))
	{
		//doToween->DoMoveY(charObj, 3.0f, 0.5f, MOVEDIR::UP);
	}
	if (gInput->GetKeyTrigger(VK_DOWN))
	{
		//doToween->DoMoveY(charObj, 3.0f, 0.5f, MOVEDIR::DOWN);
	}
	if (input.GetControllerDown(Pad_A))
	{
		//doToween->DoMoveX(charObj, 3.0f, 0.1f, MOVEDIR::LEFT);
	}

	if (gInput->GetKeyTrigger(VK_SPACE))
	{
		//doToween->DoScaleDown(charObj, 5.0f, 1.0f);
		//fade->FadeOut(fade->RIGHT, 1);
	}
	if (gInput->GetKeyTrigger(VK_RETURN))
	{
		//doToween->DoScaleUp(charObj, 5.0f, 1.0f);
		//Vector3 kari = { 4,0,0 };
		//doToween->DoMoveCurve(charObj, kari, 3.5f, 0.2f);

		//doToween->DoMove(charObj, 1.0f, 1.0f, MOVEDIR::TO_TOP_LEFT);
		//fade->FadeIn(fade->TO_TOP_RIGHT, 1);
	}

	fixedCount += 1.0f * Time::deltaTime;
	if (fixedCount > 1.0f / 60)
	{
		//doToween->Update();
		charObj->Update();



		stagescene->Update();

		//Vector3 x(charObj->mTransform.pos.x, charObj->mTransform.pos.y, charObj->mTransform.pos.z);


		//a[0]->mTransform.pos.x = x.x; // charObj->mTransform.pos;
		//a[0]->mTransform.pos.y = x.y; // charObj->mTransform.pos;

		//a[1]->mTransform.pos.x = x.x - charObj->mTransform.scale.x/2;
		//a[1]->mTransform.pos.y = x.y + charObj->mTransform.scale.y/2;

		//a[2]->mTransform.pos.x = x.x + charObj->mTransform.scale.x / 2;
		//a[2]->mTransform.pos.y = x.y + charObj->mTransform.scale.y / 2;

		//a[3]->mTransform.pos.x = x.x + charObj->mTransform.scale.x / 2;
		//a[3]->mTransform.pos.y = x.y - charObj->mTransform.scale.y / 2;

		//a[4]->mTransform.pos.x = x.x - charObj->mTransform.scale.x / 2;
		//a[4]->mTransform.pos.y = x.y - charObj->mTransform.scale.y / 2;



		//Vector3 x(stageObj[ss]->mTransform.pos.x, stageObj[ss]->mTransform.pos.y, stageObj[stageChack]->mTransform.pos.z);

		//a[0]->mTransform.pos.x = x.x; // stageObj[0]2->mTransform.pos;
		//a[0]->mTransform.pos.y = x.y; // stageObj[0]2->mTransform.pos;

		//a[1]->mTransform.pos.x = x.x - stageObj[ss]->mTransform.scale.x / 2;
		//a[1]->mTransform.pos.y = x.y + stageObj[ss]->mTransform.scale.y / 2;

		//a[2]->mTransform.pos.x = x.x + stageObj[ss]->mTransform.scale.x / 2;
		//a[2]->mTransform.pos.y = x.y + stageObj[ss]->mTransform.scale.y / 2;

		//a[3]->mTransform.pos.x = x.x + stageObj[ss]->mTransform.scale.x / 2;
		//a[3]->mTransform.pos.y = x.y - stageObj[ss]->mTransform.scale.y / 2;

		//a[4]->mTransform.pos.x = x.x - stageObj[ss]->mTransform.scale.x / 2;
		//a[4]->mTransform.pos.y = x.y - stageObj[ss]->mTransform.scale.y / 2;

		//a->mTransform.pos.z = x.z; // charObj2->mTransform.pos;
		charObj2->Update();

		a[0]->Update();
		a[1]->Update();
		a[2]->Update();
		a[3]->Update();
		a[4]->Update();

		fade->Update();

		//charObj->mTransform.pos.x += 0.5f * 1.0f * Time::slowTime;

		fixedCount = 0;
	}

	Time::Update();
}

void CMizunoScene::LateUpdate()
{
}

void CMizunoScene::Draw()
{
	//charObj->Draw();
	//charObj2->Draw();

	stagescene->Draw();
	//stageobj[0]->Draw();
	//stageobj[3]->Draw();
	//stageobj[2]->Draw();
	//stageobj[1]->Draw();
	//stageobj[0]->Draw();
	a[0]->Draw();
	a[1]->Draw();
	a[2]->Draw();
	a[3]->Draw();
	a[4]->Draw();
	//fade->Draw();
}