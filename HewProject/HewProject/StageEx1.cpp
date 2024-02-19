#include "StageEx1.h"
#include "CSceneManager.h"

StageEx1::StageEx1()
	: Stage(L"Stage4-1.csv", 4, CScene::SCENE_NAME::STAGE4_2)
{
	back->SetTexture(backTex[3]);

	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLDEX);
	nextStage = CScene::SCENE_NAME::STAGE4_2;

	D3D_LoadTexture(L"asset/Tutorial/T_10.png", &tutolialTex);
	tutorial = new Tutorial();
	tutorial->SetTexture(tutolialTex);

	stage->SetTutorial(tutorial);
}

StageEx1::~StageEx1()
{
}
