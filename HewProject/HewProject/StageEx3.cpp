#include "StageEx3.h"
#include "CSceneManager.h"

StageEx3::StageEx3()
	: Stage(L"Stage4-3.csv", 4, CScene::SCENE_NAME::STAGE4_4)
{
	back->SetTexture(backTex[3]);
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLDEX);
	nextStage = CScene::SCENE_NAME::STAGE4_4;
	BackScaleSet(1.2f);
}

StageEx3::~StageEx3()
{
}
