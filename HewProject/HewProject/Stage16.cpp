#include "Stage16.h"
#include "CSceneManager.h"
Stage16::Stage16()
	: Stage(L"Stage1-6.csv", 1, CScene::SCENE_NAME::STAGE2_1)
{
	back->SetTexture(backTex[0]);
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLD1);
	nextStage = CScene::SCENE_NAME::STAGE2_1;

	BackScaleSet(1.35f);
}

Stage16::~Stage16()
{
}
