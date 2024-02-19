#include "Stage11.h"
#include "CSceneManager.h"
#include "Tutorial.h"

Stage11::Stage11()
	: Stage(L"Stage1-1.csv", 1, CScene::SCENE_NAME::STAGE1_2)
{
	back->SetTexture(backTex[0]);
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLD1);
	
	D3D_LoadTexture(L"asset/Tutorial/T_1.png", &tutolialTex);
	D3D_LoadTexture(L"asset/Tutorial/T_2.png", &tex);
	tutorial = new Tutorial(true);
	tutorial->SetTexture(tutolialTex);
	tutorial->SetTexture(tex);

	stage->SetTutorial(tutorial);
}

Stage11::~Stage11()
{
	SAFE_RELEASE(tex);
}
