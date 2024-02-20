#include "Stage.h"
#include "CSceneManager.h"
#include"Player.h"
#include"CDirectWrite.h"
#include "TextureFactory.h"
#include"CCamera.h"
#define BACK_POSZ (1.0f)	

#define BACK_SCALETIMES (1.3f)	// ”wŒi‚Ì”{—¦

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

	Vector2 s = {SCREEN_RATIO_W * BACK_SCALETIMES, SCREEN_RATIO_H * BACK_SCALETIMES };

	back->mTransform.scale = { s.x, s.y, 1.0f };

	if (isDirectWriteUse)
	{
		dbgFloorTable = new DebugTable(stage->GetNowFloor(), true);
		dbgObjTable = new DebugTable(stage->GetNowFloor(), false);
	}
}

Stage::Stage(const wchar_t* _csvName, short int worldNum, CScene::SCENE_NAME _next)
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


	Vector2 s = { SCREEN_RATIO_W * BACK_SCALETIMES, SCREEN_RATIO_H * BACK_SCALETIMES };
	back->mTransform.scale = { s.x, s.y, 1.0f };

	stage->SetNextStageName(_next);

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
}

void Stage::LateUpdate()
{
}

void Stage::Draw()
{
	back->Draw();

	stage->Draw();
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
