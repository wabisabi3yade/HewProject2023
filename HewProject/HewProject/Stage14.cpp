#include "Stage14.h"
#include "CSceneManager.h"
Stage14::Stage14()
	: Stage(L"Stage1-4.csv", 1)
{
	back->SetTexture(backTex[0]);
	nextStage = CScene::SCENE_NAME::STAGE1_5;
}

Stage14::~Stage14()
{
}
