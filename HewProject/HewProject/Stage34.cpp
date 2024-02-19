#include "Stage34.h"
#include "CSceneManager.h"
Stage34::Stage34()
	: Stage(L"Stage3-4.csv", 3, CScene::SCENE_NAME::STAGE4_1)
{
	back->SetTexture(backTex[2]);
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLD3);
	nextStage = CScene::SCENE_NAME::STAGE4_1;
}

Stage34::~Stage34()
{
}
