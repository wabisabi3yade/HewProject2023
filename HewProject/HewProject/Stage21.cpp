#include "Stage21.h"
#include "CSceneManager.h"
Stage21::Stage21()
	: Stage(L"Stage2-1.csv", 2)
{
	back->SetTexture(backTex[1]);
}

Stage21::~Stage21()
{
}
