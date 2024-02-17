#include "Stage22.h"
#include "CSceneManager.h"
Stage22::Stage22()
	: Stage(L"Stage2-2.csv", 2)
{
	back->SetTexture(backTex[1]);
}

Stage22::~Stage22()
{
}
