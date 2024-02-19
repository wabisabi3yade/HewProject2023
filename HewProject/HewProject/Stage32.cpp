#include "Stage32.h"
#include "CSceneManager.h"
Stage32::Stage32()
	: Stage(L"Stage3-2.csv", 3, CScene::SCENE_NAME::STAGE3_3)
{
	back->SetTexture(backTex[2]);
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLD3);
	nextStage = CScene::SCENE_NAME::STAGE3_3;
}

Stage32::~Stage32()
{
}
