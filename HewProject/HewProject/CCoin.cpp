#include "CCoin.h"

CCoin::CCoin(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb,tex)
{
}

CCoin::~CCoin()
{
}

void CCoin::Update()
{
	CGridObject::Update();
}

void CCoin::Draw()
{
	CGridObject::Draw();
}
