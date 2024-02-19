#include "StageEx4.h"
#include "CSceneManager.h"

StageEx4::StageEx4()
	: Stage(L"Stage4-4.csv", 4, CScene::SCENE_NAME::WORLD4_SELECT)
{
	back->SetTexture(backTex[3]);
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLDEX);
	nextStage = CScene::SCENE_NAME::WORLD4_SELECT;
}

StageEx4::~StageEx4()
{
}
