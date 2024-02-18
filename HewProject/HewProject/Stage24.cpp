#include "Stage24.h"
#include "CSceneManager.h"
Stage24::Stage24()
	: Stage(L"Stage2-4.csv", 2)
{
	back->SetTexture(backTex[1]);
	nextStage = CScene::SCENE_NAME::STAGE3_1;
}

Stage24::~Stage24()
{
}
