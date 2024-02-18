#include "Stage31.h"
#include "CSceneManager.h"
Stage31::Stage31()
	: Stage(L"Stage3-1.csv", 3)
{
	back->SetTexture(backTex[2]);
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLD3);
	nextStage = CScene::SCENE_NAME::STAGE3_2;
}

Stage31::~Stage31()
{
}
