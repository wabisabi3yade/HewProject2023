#include "Stage12.h"
#include "CSceneManager.h"
Stage12::Stage12()
	: Stage(L"Stage1-2.csv", 1)
{
	back->SetTexture(backTex[0]);
}

Stage12::~Stage12()
{
}
