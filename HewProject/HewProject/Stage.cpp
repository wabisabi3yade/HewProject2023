#include "Stage.h"
#include "CSceneManager.h"
#include"Player.h"
#include "TextureFactory.h"
#include"CCamera.h"
#define BACK_POSZ (1.0f)	

#define BACK_SCALETIMES (1.1f)	// ”wŒi‚Ì”{—¦

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
}

Stage::Stage(const wchar_t* _csvName, short int worldNum, CScene::SCENE_NAME _next, bool _isW11)
{

	wchar_t work[256];

	wcscpy_s(work, L"asset/StageCsv/"); // •¶Žš—ñƒRƒs[ŠÖ”
	wcscat_s(work, _csvName); // •¶Žš—ñŒ‹‡ŠÖ”

	csvPath = work;

	stage = new StageScene(NULL, NULL, worldNum,_isW11);
	stage->SetNextStageName(_next);
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
}

void Stage::Init()
{

}

void Stage::Update()
{
	stage->Update();
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
	CCamera::GetInstance()->Init();
}

void Stage::BackScaleSet(float _scale)
{
	back->mTransform.scale = { SCREEN_RATIO_W * _scale,SCREEN_RATIO_H * _scale, 1.0f };
}
