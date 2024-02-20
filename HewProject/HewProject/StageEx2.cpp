#include "StageEx2.h"
#include "CSceneManager.h"

StageEx2::StageEx2()
	: Stage(L"Stage4-2.csv", 4, CScene::SCENE_NAME::STAGE4_3)
{
	back->SetTexture(backTex[3]);
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLDEX);
	nextStage = CScene::SCENE_NAME::STAGE4_3;

	BackScaleSet(1.2f);
}

StageEx2::~StageEx2()
{
}
