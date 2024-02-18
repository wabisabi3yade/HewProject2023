#include "Stage15.h"
#include "CSceneManager.h"
Stage15::Stage15()
	: Stage(L"Stage1-5.csv", 1)
{
	back->SetTexture(backTex[0]);
	nextStage = CScene::SCENE_NAME::STAGE1_6;
}

Stage15::~Stage15()
{
}
