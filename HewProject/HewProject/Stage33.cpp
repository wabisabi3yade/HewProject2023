#include "Stage33.h"
#include "CSceneManager.h"
Stage33::Stage33()
	: Stage(L"Stage3-3.csv", 3)
{
	back->SetTexture(backTex[2]);
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLD3);
	nextStage = CScene::SCENE_NAME::STAGE3_4;
}

Stage33::~Stage33()
{
}
