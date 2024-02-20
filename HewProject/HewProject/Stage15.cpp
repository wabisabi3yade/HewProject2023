#include "Stage15.h"
#include "CSceneManager.h"
Stage15::Stage15()
	: Stage(L"Stage1-5.csv", 1, CScene::SCENE_NAME::STAGE1_6)
{
	back->SetTexture(backTex[0]);
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLD1);
	nextStage = CScene::SCENE_NAME::STAGE1_6;

	D3D_LoadTexture(L"asset/Tutorial/T_6.png", &tutolialTex);
	tutorial = new Tutorial();
	tutorial->SetTexture(tutolialTex);

	stage->SetTutorial(tutorial);

	BackScaleSet(1.35f);
}

Stage15::~Stage15()
{
}
