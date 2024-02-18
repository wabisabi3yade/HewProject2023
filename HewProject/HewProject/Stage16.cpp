#include "Stage16.h"
#include "CSceneManager.h"
Stage16::Stage16()
	: Stage(L"Stage1-6.csv", 1)
{
	back->SetTexture(backTex[0]);
	nextStage = CScene::SCENE_NAME::STAGE2_1;
}

Stage16::~Stage16()
{
}
