#include "StageEx1.h"
#include "CSceneManager.h"

StageEx1::StageEx1()
	: Stage(L"Stage4-1.csv", 4)
{
	back->SetTexture(backTex[3]);

	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLDEX);
}

StageEx1::~StageEx1()
{
}
