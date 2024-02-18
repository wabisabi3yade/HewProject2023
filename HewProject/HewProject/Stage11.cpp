#include "Stage11.h"
#include "CSceneManager.h"
Stage11::Stage11()
{
	back->SetTexture(backTex[0]);
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLD1);
	nextStage = CScene::SCENE_NAME::STAGE1_1;

	stage = new StageScene(NULL, NULL, 1);
	stage->Init(L"asset/StageCsv/Stage1-1.csv");	
}

Stage11::~Stage11()
{
}
