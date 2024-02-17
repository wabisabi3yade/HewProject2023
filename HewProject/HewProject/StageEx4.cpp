#include "StageEx4.h"
#include "CSceneManager.h"

StageEx4::StageEx4()
	: Stage(L"Stage4-4.csv", 4)
{
	back->SetTexture(backTex[3]);
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLDEX);
}

StageEx4::~StageEx4()
{
}
