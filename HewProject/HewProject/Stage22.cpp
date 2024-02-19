#include "Stage22.h"
#include "CSceneManager.h"
Stage22::Stage22()
	: Stage(L"Stage2-2.csv", 2, CScene::SCENE_NAME::STAGE2_3)
{
	back->SetTexture(backTex[1]);
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLD2);
	nextStage = CScene::SCENE_NAME::STAGE2_3;

	D3D_LoadTexture(L"asset/Tutorial/T_8.png", &tutolialTex);
	tutorial = new Tutorial();
	tutorial->SetTexture(tutolialTex);

	stage->SetTutorial(tutorial);
}

Stage22::~Stage22()
{
}
