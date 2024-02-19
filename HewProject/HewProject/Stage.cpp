#include "Stage.h"
#include "CSceneManager.h"
#include"Player.h"
#include"CDirectWrite.h"
#include "TextureFactory.h"
#include"CCamera.h"
#define BACK_POSZ (1.0f)	

Stage::Stage()
{
	TextureFactory* texFactory = TextureFactory::GetInstance();
	backTex[0] = texFactory->Fetch(L"asset/Background/Stage1.png");
	backTex[1] = texFactory->Fetch(L"asset/Background/Stage2.png");
	backTex[2] = texFactory->Fetch(L"asset/Background/Stage3.png");
	backTex[3] = texFactory->Fetch(L"asset/Background/StageEX.png");

	D3D_CreateSquare({ 1,1 }, &backBuffer);
	back = new CObject(backBuffer, NULL);
	back->mTransform.pos.z = BACK_POSZ;
	back->mTransform.scale = { SCREEN_RATIO_W, SCREEN_RATIO_H, 1.0f };

	if (isDirectWriteUse)
	{
		dbgFloorTable = new DebugTable(stage->GetNowFloor(), true);
		dbgObjTable = new DebugTable(stage->GetNowFloor(), false);
	}
}

Stage::Stage(const wchar_t* _csvName, short int worldNum)
{

	wchar_t work[256];

	wcscpy_s(work, L"asset/StageCsv/"); // •¶Žš—ñƒRƒs[ŠÖ”
	wcscat_s(work, _csvName); // •¶Žš—ñŒ‹‡ŠÖ”

	csvPath = work;

	stage = new StageScene(NULL, NULL, worldNum);
	stage->Init(csvPath);

	TextureFactory* texFactory =  TextureFactory::GetInstance();
	backTex[0] = texFactory->Fetch(L"asset/Background/Stage1.png");
	backTex[1] = texFactory->Fetch(L"asset/Background/Stage2.png");
	backTex[2] = texFactory->Fetch(L"asset/Background/Stage3.png");
	backTex[3] = texFactory->Fetch(L"asset/Background/StageEX.png");

	D3D_CreateSquare({ 1,1 }, &backBuffer);
	back = new CObject(backBuffer, NULL);
	back->mTransform.pos.z = BACK_POSZ;
	back->mTransform.scale = { SCREEN_RATIO_W, SCREEN_RATIO_H, 1.0f };

	if (isDirectWriteUse)
	{
		dbgFloorTable = new DebugTable(stage->GetNowFloor(), true);
		dbgObjTable = new DebugTable(stage->GetNowFloor(), false);
	}
}

void Stage::Init()
{

}

void Stage::Update()
{
	stage->Update();


	if (isDirectWriteUse)
	{
		dbgFloorTable->SetTable(stage->GetNowFloor());
		dbgObjTable->SetTable(stage->GetNowFloor());

	}

	if (gInput->GetKeyTrigger(VK_CONTROL))
	{
		Fade::GetInstance()->FadeIn(Fade::STATE::FADE_OUT, nullptr, CScene::SCENE_NAME::STAGE1);
	}
}

void Stage::LateUpdate()
{
}

void Stage::Draw()
{
	back->Draw();

	stage->Draw();
	if (isDirectWriteUse)
	{
		dbgFloorTable->Draw();
		dbgObjTable->Draw();

		std::string canMoveDirCheck;
		bool* canmove = stage->GetPlayer()->GetCanMoveDir();
		if (canmove[0] == 1)
		{
			canMoveDirCheck.append("1");
		}
		else
		{
			canMoveDirCheck.append("0");
		}
		if (canmove[1] == 1)
		{
			canMoveDirCheck.append("1");
		}
		else
		{
			canMoveDirCheck.append("0");
		}
		if (canmove[2] == 1)
		{
			canMoveDirCheck.append("1");
		}
		else
		{
			canMoveDirCheck.append("0");
		}
		if (canmove[3] == 1)
		{
			canMoveDirCheck.append("1");
		}
		else
		{
			canMoveDirCheck.append("0");
		}


		Write->SetFont(Font::HG_Gyosyo, nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 30, L"ja-jp", DWRITE_TEXT_ALIGNMENT_LEADING, D2D1::ColorF(D2D1::ColorF::Green));
		Write->DrawString(canMoveDirCheck, DirectX::XMFLOAT2(30, 10), D2D1_DRAW_TEXT_OPTIONS_NONE);
	}
}

Stage::~Stage()
{
	SAFE_RELEASE(backBuffer);
	CLASS_DELETE(back);

	SAFE_RELEASE(tutolialTex);
	CLASS_DELETE(tutorial);

	CLASS_DELETE(stage);
	CLASS_DELETE(dbgFloorTable);
	CLASS_DELETE(dbgObjTable);
	CCamera::GetInstance()->Init();
}
