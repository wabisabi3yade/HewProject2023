#include "Stage34.h"
#include "CSceneManager.h"
Stage34::Stage34()
	: Stage(L"Stage3-4.csv")
{
	back->SetTexture(backTex[2]);
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLD3);
}

Stage34::~Stage34()
{
}
