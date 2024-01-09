#include "CChili.h"

CChili::CChili(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb,tex)
{
}

CChili::~CChili()
{
}

void CChili::Update()
{
	CGridObject::Update();
}

void CChili::Draw()
{
	CGridObject::Draw();
}
