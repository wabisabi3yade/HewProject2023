#include "Stage12.h"
#include "CSceneManager.h"
Stage12::Stage12()
	: Stage(L"Stage1-2.csv", 1, CScene::SCENE_NAME::STAGE1_3)
{
	back->SetTexture(backTex[0]);
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLD1);
	nextStage = CScene::SCENE_NAME::STAGE1_2;

	D3D_LoadTexture(L"asset/Tutorial/T_4.png", &tutolialTex);
	tutorial = new Tutorial();
	tutorial->SetTexture(tutolialTex);

	stage->SetTutorial(tutorial);
}

Stage12::~Stage12()
{
}
