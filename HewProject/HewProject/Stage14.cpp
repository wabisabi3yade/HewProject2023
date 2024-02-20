#include "Stage14.h"
#include "CSceneManager.h"
Stage14::Stage14()
	: Stage(L"Stage1-4.csv", 1, CScene::SCENE_NAME::STAGE1_5)
{
	back->SetTexture(backTex[0]);
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLD1);
	nextStage = CScene::SCENE_NAME::STAGE1_5;

	D3D_LoadTexture(L"asset/Tutorial/T_5.png", &tutolialTex);
	tutorial = new Tutorial();
	tutorial->SetTexture(tutolialTex);

	stage->SetTutorial(tutorial);

	BackScaleSet(1.3f);
}

Stage14::~Stage14()
{
}
