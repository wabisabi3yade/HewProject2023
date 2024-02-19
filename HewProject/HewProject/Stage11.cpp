#include "Stage11.h"
#include "CSceneManager.h"
#include "Tutorial.h"

#define TEXT_POSZ (-0.35f)

Stage11::Stage11()
	: Stage(L"Stage1-1.csv", 1, CScene::SCENE_NAME::STAGE1_2)
{
	back->SetTexture(backTex[0]);
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLD1);
	
	D3D_LoadTexture(L"asset/Tutorial/T_1.png", &tutolialTex);
	D3D_LoadTexture(L"asset/Tutorial/T_2.png", &tex);
	tutorial = new Tutorial(true);
	tutorial->SetTexture(tutolialTex);
	tutorial->SetTexture(tex);

	D3D_LoadTexture(L"asset/UI/T_GetProtein.png", &getProteinTex);
	D3D_LoadTexture(L"asset/Tutorial/T_GoChest.png", &goChestTex);

	stage->SetTutorial(tutorial);

	text = new UI(backBuffer, getProteinTex);

	text->mTransform.pos = { 5.0f, 3.0f, TEXT_POSZ };
	text->mTransform.scale = { 9.0f, 2.0f, TEXT_POSZ };
}

void Stage11::Update()
{
	Stage::Update();

	//if()
}

void Stage11::Draw()
{
	Stage::Draw();

	text->Draw();
}

Stage11::~Stage11()
{
	SAFE_RELEASE(tex);
	CLASS_DELETE(text);
	SAFE_RELEASE(getProteinTex);
	SAFE_RELEASE(goChestTex);
}
