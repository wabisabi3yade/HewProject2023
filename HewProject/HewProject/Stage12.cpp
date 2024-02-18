#include "Stage12.h"
#include "CSceneManager.h"
Stage12::Stage12()
	: Stage(L"Stage1-2.csv", 1)
{
	back->SetTexture(backTex[0]);
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLD1);
	nextStage = CScene::SCENE_NAME::STAGE1_2;
}

Stage12::~Stage12()
{
}
