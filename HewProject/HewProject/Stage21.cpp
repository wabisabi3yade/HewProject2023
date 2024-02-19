#include "Stage21.h"
#include "CSceneManager.h"
Stage21::Stage21()
	: Stage(L"Stage2-1.csv", 2, CScene::SCENE_NAME::STAGE2_2)
{
	back->SetTexture(backTex[1]);
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLD2);
	nextStage = CScene::SCENE_NAME::STAGE2_2;

	D3D_LoadTexture(L"asset/Tutorial/T_7.png", &tutolialTex);
	tutorial = new Tutorial();
	tutorial->SetTexture(tutolialTex);

	stage->SetTutorial(tutorial);
}

Stage21::~Stage21()
{
}
