#include "CChoco.h"

CChoco::CChoco(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb,tex)
{
}

CChoco::~CChoco()
{
}

void CChoco::Update()
{
	CGridObject::Update();
}

void CChoco::Draw()
{
	CGridObject::Draw();
}
