#include "Stage23.h"
#include "CSceneManager.h"
Stage23::Stage23()
	: Stage(L"Stage2-3.csv", 2)
{
	back->SetTexture(backTex[1]);
	nextStage = CScene::SCENE_NAME::STAGE2_4;
}

Stage23::~Stage23()
{
}
