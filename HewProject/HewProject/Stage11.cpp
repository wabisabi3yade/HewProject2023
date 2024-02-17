#include "Stage11.h"
#include "CSceneManager.h"
Stage11::Stage11()
	: Stage(L"Stage1-1.csv", 1)
{
	back->SetTexture(backTex[0]);
}

Stage11::~Stage11()
{
}
