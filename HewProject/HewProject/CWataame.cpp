#include "CWataame.h"

CWataame::CWataame(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb,tex)
{
}

CWataame::~CWataame()
{
}

void CWataame::Update()
{
	CGridObject::Update();
}

void CWataame::Draw()
{
	CGridObject::Draw();
}
