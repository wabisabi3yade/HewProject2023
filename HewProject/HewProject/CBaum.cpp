#include "CBaum.h"

CBaum::CBaum(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb,tex)
{
}

CBaum::~CBaum()
{
}

void CBaum::Update()
{
	CGridObject::Update();
}

void CBaum::Draw()
{
	CGridObject::Draw();
}
