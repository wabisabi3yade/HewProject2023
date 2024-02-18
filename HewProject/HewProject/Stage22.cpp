#include "Stage22.h"
#include "CSceneManager.h"
Stage22::Stage22()
	: Stage(L"Stage2-2.csv", 2)
{
	back->SetTexture(backTex[1]);
	nextStage = CScene::SCENE_NAME::STAGE2_3;
}

Stage22::~Stage22()
{
}
