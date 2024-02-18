#include "Stage13.h"
#include "CSceneManager.h"
Stage13::Stage13()
	: Stage(L"Stage1-3.csv", 1)
{
	back->SetTexture(backTex[0]);
	nextStage = CScene::SCENE_NAME::STAGE1_3;
}

Stage13::~Stage13()
{
}
