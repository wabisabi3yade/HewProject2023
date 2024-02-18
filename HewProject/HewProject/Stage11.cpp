#include "Stage11.h"
#include "CSceneManager.h"
Stage11::Stage11()
	: Stage(L"Stage1-1.csv", 1)
{
	back->SetTexture(backTex[0]);
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLD1);
	nextStage = CScene::SCENE_NAME::STAGE1_1;
}

Stage11::~Stage11()
{
}
