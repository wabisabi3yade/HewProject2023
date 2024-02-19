#include "Stage13.h"
#include "CSceneManager.h"
Stage13::Stage13()
	: Stage(L"Stage1-3.csv", 1)
{
	back->SetTexture(backTex[0]);
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLD1);
	nextStage = CScene::SCENE_NAME::STAGE1_3;
}

Stage13::~Stage13()
{
}
