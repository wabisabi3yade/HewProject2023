#include "StageEx4.h"
#include "CSceneManager.h"

StageEx4::StageEx4()
	: Stage(L"Stage4-4.csv")
{
	back->SetTexture(backTex[3]);
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLDEX);
}

StageEx4::~StageEx4()
{
}
