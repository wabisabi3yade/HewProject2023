#include "Stage33.h"
#include "CSceneManager.h"
Stage33::Stage33()
	: Stage(L"Stage3-3.csv")
{
	back->SetTexture(backTex[2]);
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLD3);
}

Stage33::~Stage33()
{
}
