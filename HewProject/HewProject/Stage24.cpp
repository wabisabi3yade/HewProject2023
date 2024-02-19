#include "Stage24.h"
#include "CSceneManager.h"
Stage24::Stage24()
	: Stage(L"Stage2-4.csv", 2, CScene::SCENE_NAME::STAGE3_1)
{
	back->SetTexture(backTex[1]);
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLD2);
	nextStage = CScene::SCENE_NAME::STAGE3_1;
}

Stage24::~Stage24()
{
}
